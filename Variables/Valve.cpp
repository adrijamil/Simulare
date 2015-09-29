#include "stdafx.h"
#include "Valve.h"


Valve::Valve()
{
}


Valve::Valve(string name)
{
	_name = name;
}

Valve::~Valve()
{
}

bool Valve::Solve()
{
	if (_issolved == true)
	{
		return true;

	}
	bool enthalpypassed = false;
	bool flowpassed = false;
	bool pressuresolved = false;
	bool comppassed = false;
	bool retval = false;
	int nflowspecs = 0;
	double* X;
	int ncomps;
	double F=-32767;
	double H;

	
	if (_inletstreams == 0 || _outletstreams == 0)
	{
		return false;
	}

	//pass variable pointers
	RealVariable* P1 = _inletstreams->Pressure();
	RealVariable* P2 = _outletstreams->Pressure();
	RealVariable* F1 = _inletstreams->MassFlow();
	RealVariable* F2 = _outletstreams->MassFlow();
	RealVariable* X1 = _inletstreams->Composition();
	RealVariable* X2 = _outletstreams->Composition();
	RealVariable* H1 = _inletstreams->MolarEnthalpy();
	RealVariable* H2 = _outletstreams->MolarEnthalpy();

	//check flow

	if (F1->IsKnown() && F2->IsCalculated())
	{
		F = F1->GetValue();
		F2->SetValue(F);

	}
	else if (F2->IsKnown() && F2->IsCalculated())
	{
		F = F2->GetValue();
		F1->SetValue(F);
	}

	if (F1->IsKnown() && F2->IsKnown())
	{
		flowpassed = true;
	}

	ncomps = _inletstreams->NComps();

	//check enthalpy
	if (H1->IsKnown() && H2->IsCalculated())
	{
		H = H1->GetValue();
		H2->SetValue(H);
	}
	else if (H2->IsKnown() && H1->IsCalculated())
	{
		H = H1->GetValue();
		H1->SetValue(H);
	}

	if (H2->IsKnown() && H1->IsKnown())
	{
		enthalpypassed = true;
	}

	if (X1->IsKnown() && X2->IsCalculated())
	{
		X = X1->GetValues();
		X2->SetValues(3, X);
	}
	else if (X2->IsKnown() && X1->IsCalculated())
	{
		X = X2->GetValues();
		X1->SetValues(3, X);
	}

	if (X1->IsKnown() && X2->IsKnown())
	{
		comppassed = true;
	}

	if (P1->IsKnown())
	{
		if (P2->IsKnown())
		{
			if (_k_resistance->IsKnown())
			{
				if (F1->IsCalculated() && F2->IsCalculated())
				{
					CalcMode = KP1P2;
				}	
			}
			else if (F1->IsKnown() || F2->IsKnown())
			{
				if (_k_resistance->IsCalculated())
				{
					CalcMode = FP1P2;

				}
			}
		}
		else if (F1->IsKnown() || F2->IsKnown())
		{
			if (_k_resistance->IsKnown())
			{
				CalcMode = FKP1;

			}
		}
	}
	else if (P2->IsKnown())
	{
		if (F1->IsKnown() || F2->IsKnown())
		{
			if (_k_resistance->IsKnown())
			{
				CalcMode = FKP2;

			}
		}
	}
	//enum CalcModeEnum { FKP1,FKP2,FP1P2,KP1P2}
double p2, p1, k;
	switch (CalcMode)
	{
	case Valve::FKP1:
		//calc P2
		
		p1 = P1->GetValue();
		k = _k_resistance->GetValue();
		p2 = p1 - F*F / k / k;
		P2->SetValue(p2);
		 pressuresolved = true;
		break;
	case Valve::FKP2:
		//calc P1

		p2 = P2->GetValue();
		k = _k_resistance->GetValue();
		p1 = p2 + (F * F )/( k * k);
		P1->SetValue(p1);
		pressuresolved = true;
		break;
	case Valve::FP1P2:
		//calc k

		p2 = P2->GetValue();
		p1 = P1->GetValue();
		k = F / pow((p1 - p2), 0.5);
		_k_resistance->SetValue(k);
		pressuresolved = true;
		break;
	case Valve::KP1P2:
		//calc F

		p2 = P2->GetValue();
		p1 = P1->GetValue();
		k = _k_resistance->GetValue();
		F = k*pow((p1 - p2), 0.5);
		F1->SetValue(F);
		F2->SetValue(F);
		pressuresolved = true;
		break;
	default:
		break;
	}

	if (flowpassed&&pressuresolved&&enthalpypassed)
	{
		_issolved = true;

		retval = true;
	}
	return retval;
}


void Valve::Output()
{
	cout << "\n";
	cout << _name << "\n";

	cout << "K resistance  [kPa-kg/h] " << K_Resistance()->GetValue() << "\n";
}