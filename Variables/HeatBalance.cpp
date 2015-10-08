#include "stdafx.h"
#include "HeatBalance.h"
#include "UnitOp.h"
#include "Stream.h"

HeatBalance::HeatBalance()
{
}


HeatBalance::~HeatBalance()
{
}

bool HeatBalance::_altsolve()
{
	int nenthknown=0;
	int nflowknown=0; //mol basis only- let component balance handle passing of mass flow if necessary
	int nin, nout;
	int Qpresent = 0;
	int Qknown = 0;
	int DOF = 0;
	double Q = -32767;
	double H = -32767;
	double F = -32767;
	bool retval=false;
	nin = _parent->NInlets();
	nout = _parent->NOutlets();
	double sumH=0;
	RealVariable* Uknown = 0;
	//check molar flows
	enum CalcModeEnum {CANNOTSOLVE,CALCH, CALCQ,CALCF};
	CalcModeEnum CalcMode = CANNOTSOLVE;

	for (int i = 0; i < nin; i++)
	{
		if (_parent->GetStream(i, INLET)->MolarFlow()->IsKnown())
		{
			nflowknown++;
			F = _parent->GetStream(i, INLET)->MolarFlow()->GetValue();
		}
		else
		{
			CalcMode = CALCF;
			Uknown = _parent->GetStream(i, INLET)->MolarFlow();
			H = _parent->GetStream(i, INLET)->MolarEnthalpy()->GetValue();
		}
	}

	for (int i = 0; i < nin; i++)
	{
		if (_parent->GetStream(i, OUTLET)->MolarFlow()->IsKnown())
		{
			nflowknown++;
			F = _parent->GetStream(i, OUTLET)->MolarFlow()->GetValue();
		}
		else
		{
			CalcMode = CALCF;
			Uknown = _parent->GetStream(i, OUTLET)->MolarFlow();
			H = _parent->GetStream(i, OUTLET)->MolarEnthalpy()->GetValue();
		}
	}

	//check enthalpies
	for (int i = 0; i < nin; i++)
	{
		if (_parent->GetStream(i, INLET)->MolarEnthalpy()->IsKnown())
		{
			nenthknown++;
		}
		else
		{
			CalcMode = CALCH;
			Uknown = _parent->GetStream(i, INLET)->MolarEnthalpy();
			
		}
	}

	for (int i = 0; i < nin; i++)
	{
		if (_parent->GetStream(i, OUTLET)->MolarEnthalpy()->IsKnown())
		{
			nenthknown++;
		}
		else
		{
			CalcMode = CALCH;
			Uknown = _parent->GetStream(i, OUTLET)->MolarEnthalpy();
		}
	}

	if (_heatinput != 0)
	{
		Qpresent = 1;
		if (_heatinput->IsKnown())
		{
			Qknown++;
		}
		else
		{
			CalcMode = CALCQ;
			Uknown =_heatinput;
		}
	}
	
	DOF = DOF + Qpresent + 2*nin + 2*nout;
	DOF = DOF-nenthknown - nflowknown - Qknown;
	if (DOF == 1)//2 equations
	{
		
		for (int i = 0; i < nin; i++)
		{
			cout << _parent->GetStream(i, INLET)->MolarEnthalpy()->GetValue() << "\n";
			cout << _parent->GetStream(i, INLET)->MolarFlow()->GetValue()<<"\n";
			if (_parent->GetStream(i, INLET)->MolarFlow()->IsKnown() &&  _parent->GetStream(i, INLET)->MolarEnthalpy()->IsKnown())
			{
				sumH = sumH + _parent->GetStream(i, INLET)->MolarFlow()->GetValue()*_parent->GetStream(i, INLET)->MolarEnthalpy()->GetValue();
			}
		}
		for (int i = 0; i < nout; i++)
		{
			if ( _parent->GetStream(i, OUTLET)->MolarFlow()->IsKnown() && _parent->GetStream(i, OUTLET)->MolarEnthalpy()->IsKnown())
			{
				sumH = sumH + _parent->GetStream(i, OUTLET)->MolarFlow()->GetValue()*_parent->GetStream(i, OUTLET)->MolarEnthalpy()->GetValue();
			}
		}

		if (Uknown!=_heatinput&&_heatinput!=0)
		{
			sumH = sumH + _heatinput->GetValue();
		}

		switch (CalcMode)
		{
			case CalcModeEnum::CALCQ:
				Q = sumH;
				_heatinput->SetValue(Q);
				retval = true;
				break;
			case CalcModeEnum::CALCH:
				retval = true;
				H = sumH / F;
				Uknown->SetValue(H);
				break;
			case CalcModeEnum::CALCF:
				retval = true;
				F = sumH / H;
				Uknown->SetValue(F);
				
		}
		


	}
	else if (DOF == 0)
	{
		retval = true;
	}

	return retval;
}

bool HeatBalance::Solve()
{
	bool dabool = _altsolve();
	return dabool;

	//check DOF
	//Solve if can
	//do by molar flow first - 
	//if I have n streams, n-1 streams need to be known;
	int nspecced = 0;
	int nin, nout;
	nin = _parent->NInlets();
	nout = _parent->NOutlets();
	Stream* UnknownStrm = 0;
	bool CalcH = false;
	int flowdir;
	double sumH = 0;
	double* X;
	bool enthalpypassed = false;
	bool comppassed = false;
	bool calcflow = false;
	Stream* KnownEnth=0;

	//all flows need to be known
	for (int i = 0; i < nin; i++)
	{
		if (!_parent->GetStream(i, INLET)->MolarFlow()->IsKnown())
		{
			calcflow = true;
		}
	}

	for (int i = 0; i < nout; i++)
	{
		if (!_parent->GetStream(i, OUTLET)->MolarFlow()->IsKnown())
		{
			calcflow = true;
		}
	}

	//check enthalpies
	for (int i = 0; i < nin; i++)
	{
		if (_parent->GetStream(i, INLET)->MolarEnthalpy()->IsKnown())
		{
			nspecced++;
			KnownEnth = _parent->GetStream(i, INLET);
		}
		else
		{
			flowdir = -1;
			UnknownStrm = _parent->GetStream(i, INLET);
		}
	}

	for (int i = 0; i < nout; i++)
	{
		cout << _parent->GetStream(i, OUTLET)->MolarEnthalpy()->IsKnown();
		if (_parent->GetStream(i, OUTLET)->MolarEnthalpy()->IsKnown())
		{
			nspecced++;
			KnownEnth = _parent->GetStream(i, OUTLET);
		}
		else
		{
			flowdir = 1;
			UnknownStrm = _parent->GetStream(i, OUTLET);
		}
	}

	if (_heatinput != 0)
	{
		if (_heatinput->IsKnown())
		{
			nspecced++;
		}
		else
		{
			CalcH = true;
		}
	}
	else
	{
		nspecced++; //meaning it is 0
	}

	if (nin == 1&&nout>1)//means splitter take one enthalpy and pass to the rest
	{
		if (nspecced -1> 0) //minus one to account for specced heat
		{
			sumH = KnownEnth->MolarEnthalpy()->GetValue();
			for (int i = 0; i < nin; i++)
			{
				if (KnownEnth != _parent->GetStream(i, INLET))
				{
					_parent->GetStream(i, INLET)->MolarEnthalpy()->SetValue(sumH);
				}
			}
			for (int i = 0; i < nout; i++)
			{
				if (KnownEnth != _parent->GetStream(i, OUTLET))
				{
					_parent->GetStream(i, OUTLET)->MolarEnthalpy()->SetValue(sumH);
				}
			}
			enthalpypassed = true;
		}
	}
	else
	{
		if (-nspecced + nin + nout==0)//DOF is 0
		{
			for (int i = 0; i < nin; i++)
			{
				if (UnknownStrm != _parent->GetStream(i, INLET) && _parent->GetStream(i, INLET)->MolarFlow()->IsKnown())
				{
					sumH = sumH + _parent->GetStream(i, INLET)->MolarFlow()->GetValue()*_parent->GetStream(i, INLET)->MolarEnthalpy()->GetValue();
				}

			}
			for (int i = 0; i < nout; i++)
			{
				if (UnknownStrm != _parent->GetStream(i, OUTLET) && _parent->GetStream(i, OUTLET)->MolarFlow()->IsKnown())
				{
					sumH = sumH - _parent->GetStream(i, OUTLET)->MolarFlow()->GetValue()*_parent->GetStream(i, OUTLET)->MolarEnthalpy()->GetValue();
				}
			}
			if (_heatinput != 0)
			{
				if (_heatinput->IsKnown())
				{
					sumH = sumH + _heatinput->GetValue();
				}
			}

			if (UnknownStrm != 0)
			{
				sumH = sumH / UnknownStrm->MolarFlow()->GetValue();
				UnknownStrm->MolarEnthalpy()->SetValue(flowdir*sumH);
			}
			else
			{
				if (calcflow)
				{
					_parent->GetStream(0, INLET)->MolarFlow()->SetValue(sumH / (_parent->GetStream(0, OUTLET)->MolarEnthalpy()->GetValue() - _parent->GetStream(0, INLET)->MolarEnthalpy()->GetValue()));
				}
				else
				{
					_heatinput->SetValue(-sumH);
				}
					
			}
			enthalpypassed = true;
		}
	}
	

	if (nspecced-1 == nin + nout)
	{
		//if all known assume solved this part
		enthalpypassed = true;
	}

	return enthalpypassed;
}