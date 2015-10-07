#include "stdafx.h"
#include "SimpleResistanceEquation.h"
#include "UnitOp.h"
#include "Stream.h"

SimpleResistanceEquation::SimpleResistanceEquation()
{
}


SimpleResistanceEquation::~SimpleResistanceEquation()
{
}

bool SimpleResistanceEquation::Solve()
{
	double F = -32767;
	enum CalcModeEnum { CANNOTSOLVE, FKP1, FKP2, FP1P2, KP1P2,SOLVED}; // need to know if solved or not
	CalcModeEnum CalcMode = CANNOTSOLVE;
	bool pressuresolved = false;
	RealVariable* P1 = _parent->GetStream(0, INLET)->Pressure();
	RealVariable* P2 = _parent->GetStream(0, OUTLET)->Pressure();
	RealVariable* F1 = _parent->GetStream(0, INLET)->MassFlow();
	RealVariable* F2 = _parent->GetStream(0, OUTLET)->MassFlow();
	////check flow
	if (_solved)
	{
		return true;
	}

	if (F1->IsKnown() && F2->IsCalculated())
	{
		F = F1->GetValue();
	}
	else if (F2->IsKnown() && F1->IsCalculated())
	{
		F = F2->GetValue();
	}

	double p2, p1, k;
	//if DP is known set P1,P2 or if P1,P2  is known set DP;
	if (_pressuredrop->IsKnown())
	{
		if (P1->IsKnown())
		{
			p2 = P1->GetValue() - _pressuredrop->GetValue();
			P2->SetValue(p2);

		}
		else if (P2->IsKnown())
		{
			p1 = P2->GetValue() + _pressuredrop->GetValue();
			P1->SetValue(p1);
		}
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
				/*else
				{
					CalcMode = SOLVED;
				}*/
			}
			else if (F1->IsKnown() || F2->IsKnown())
			{
				if (_k_resistance->IsCalculated())
				{
					CalcMode = FP1P2;

				}
				/*else
				{
				CalcMode = SOLVED;
				}*/
			}
		}
		else if (F1->IsKnown() || F2->IsKnown())
		{
			if (_k_resistance->IsKnown())
			{
				CalcMode = FKP1;
			}
			/*else
			{
			CalcMode = SOLVED;
			}*/
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
			/*else
			{
			CalcMode = SOLVED;
			}*/
		}
	}
	//enum CalcModeEnum { FKP1,FKP2,FP1P2,KP1P2}

	if (CalcMode == CANNOTSOLVE)
	{
		return false;
	}
	else if (CalcMode == SOLVED)
	{
		return true;
	}

	switch (CalcMode)
	{
	case FKP1:
		//calc P2

		p1 = P1->GetValue();
		k = _k_resistance->GetValue();
		p2 = p1 - F*F / k / k;
		P2->SetValue(p2);
		_pressuredrop->SetValue(p1 - p2);
		pressuresolved = true;
		break;
	case FKP2:
		//calc P1

		p2 = P2->GetValue();
		k = _k_resistance->GetValue();
		p1 = p2 + (F * F) / (k * k);
		P1->SetValue(p1);
		_pressuredrop->SetValue(p1 - p2);
		pressuresolved = true;
		break;
	case FP1P2:
		//calc k

		p2 = P2->GetValue();
		p1 = P1->GetValue();
		k = F / pow((p1 - p2), 0.5);
		_k_resistance->SetValue(k);
		_pressuredrop->SetValue(p1 - p2);
		pressuresolved = true;
		break;
	case KP1P2:
		//calc F

		p2 = P2->GetValue();
		p1 = P1->GetValue();
		k = _k_resistance->GetValue();
		F = k*pow((p1 - p2), 0.5);
		_pressuredrop->SetValue(p1 - p2);
		F1->SetValue(F);
		F2->SetValue(F);
		pressuresolved = true;
		break;
	default:
		break;
	}

	if (pressuresolved)
	{
		_solved = true;
	}

	return pressuresolved;
}
