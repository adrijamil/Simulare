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
	bool flowpassed = false;
	bool pressuresolved = false;
	bool comppassed = false;
	bool retval = false;
	int nflowspecs = 0;
	double* X;
	int ncomps;
	double F=-32767;
	
	if (_inletstreams == 0 || _outletstreams == 0)
	{
		return false;
	}

	RealVariable* P1 = _inletstreams->Pressure();
	RealVariable* P2 = _outletstreams->Pressure();
	RealVariable* F1 = _inletstreams->Pressure();
	RealVariable* F2 = _outletstreams->Pressure();
	RealVariable* X1 = _inletstreams->Composition();
	RealVariable* X2 = _outletstreams->Composition();

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

	//check composition
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
					retval = true;
				}
			}
		}
		else if (F1->IsKnown() || F2->IsKnown())
		{
			if (_k_resistance->IsKnown())
			{
				CalcMode = FKP1;
				retval = true;
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
				retval = true;
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
		p1 = p2 + F*F / k / k;
		P1->SetValue(p1);
		pressuresolved = true;
		break;
	case Valve::FP1P2:
		//calc k

		p2 = P2->GetValue();
		p1 = P1->GetValue();
		k = F / pow((p2 - p2), 0.5);
		_k_resistance->SetValue(k);
		pressuresolved = true;
		break;
	case Valve::KP1P2:
		//calc F

		p2 = P2->GetValue();
		p1 = P1->GetValue();
		k = _k_resistance->GetValue();
		F = k*pow((p2 - p2), 0.5);
		F1->SetValue(F);
		F2->SetValue(F);
		pressuresolved = true;
		break;
	default:
		break;
	}

	if (flowpassed&&pressuresolved)
	{
		retval = true;
	}
	return retval;
}


bool Valve::CanSolve()
{
	bool retval=false;
	int nflowspecs = 0;

	if (_inletstreams == 0 || _outletstreams == 0)
	{
		return false;
	}

	RealVariable* P1 = _inletstreams->Pressure();
	RealVariable* P2 = _outletstreams->Pressure();
	RealVariable* F1 = _inletstreams->Pressure();
	RealVariable* F2 = _outletstreams->Pressure();
	
	if (P1->IsKnown())
	{
		if (P2->IsKnown())
		{
			if (_k_resistance->IsKnown())
			{
				if (F1->IsCalculated() && F2->IsCalculated())
				CalcMode = KP1P2;
				retval = true;
			}
			else if (F1->IsKnown() || F2->IsKnown())
			{
				if (_k_resistance->IsCalculated())
				{
					CalcMode = FP1P2;
					retval = true;
				}
			}
		}
		else if (F1->IsKnown() || F2->IsKnown())
		{
			if (_k_resistance->IsKnown())
			{
				CalcMode = FKP1;
				retval = true; 
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
				retval = true;
			}
		}
	}
	return retval;
}