#include "stdafx.h"
#include "ComponentBalance.h"
#include "UnitOp.h"
#include "Stream.h"

bool ComponentBalance::Solve()
{
	//check DOF
	//Solve if can
	//do by molar flow first - 

	int nspecced = 0;
	int nmassspecced = 0;
	int nmolspecced = 0;
	int nin, nout;
	nin = _parent->NInlets();
	nout = _parent->NOutlets();
	RealVariable* UnknownFmol = 0;
	RealVariable* UnknownFmass = 0;
	RealVariable* KnownX = 0;
	Stream* UnknownX = 0;
	double sumF = 0;
	double* X;
	bool molflowpassed = false;
	bool massflowpassed = false;
	bool comppassed = false;
	int flowdir;
	//check mole flows
	for (int i = 0; i < nin; i++)
	{
		if (_parent->GetStream(i, INLET)->MolarFlow()->IsKnown())
		{
			nmolspecced++;
		}
		else
		{
			flowdir = -1;
			UnknownFmol = _parent->GetStream(i, INLET)->MolarFlow();
		}
	}

	for (int i = 0; i < nout; i++)
	{
		if (_parent->GetStream(i, OUTLET)->MolarFlow()->IsKnown())
		{
			nmolspecced++;
		}
		else
		{
			flowdir = 1;
			UnknownFmol = _parent->GetStream(i, OUTLET)->MolarFlow();
		}
	}


	//chekc mass flows
	for (int i = 0; i < nin; i++)
	{
		if (_parent->GetStream(i, INLET)->MassFlow()->IsKnown())
		{
			nmassspecced++;
		}
		else
		{
			flowdir = -1;
			UnknownFmass = _parent->GetStream(i, INLET)->MassFlow();
		}
	}

	for (int i = 0; i < nout; i++)
	{
		if (_parent->GetStream(i, OUTLET)->MassFlow()->IsKnown())
		{
			nmassspecced++;
		}
		else
		{
			flowdir = 1;
			UnknownFmass = _parent->GetStream(i, OUTLET)->MassFlow();
		}
	}

	if (nmolspecced + 1 == nin + nout)//DOF is 0
	{
		for (int i = 0; i < nin; i++)
		{
			if (_parent->GetStream(i, INLET)->MolarFlow()->IsKnown()){ sumF = sumF + _parent->GetStream(i, INLET)->MolarFlow()->GetValue(); }
		}
		for (int i = 0; i < nout; i++)
		{
			if (_parent->GetStream(i, OUTLET)->MolarFlow()->IsKnown()){ sumF = sumF - _parent->GetStream(i, OUTLET)->MolarFlow()->GetValue(); }
		}
		if (UnknownFmol != 0){ UnknownFmol->SetValue(flowdir*sumF); }
		sumF = 0;
		molflowpassed = true;
	}
	if (nmassspecced + 1 == nin + nout)
	{
		for (int i = 0; i < nin; i++)
		{
			if (_parent->GetStream(i, INLET)->MassFlow()->IsKnown()){ sumF = sumF + _parent->GetStream(i, INLET)->MassFlow()->GetValue(); }
		}
		for (int i = 0; i < nout; i++)
		{
			if (_parent->GetStream(i, OUTLET)->MassFlow()->IsKnown()){ sumF = sumF - _parent->GetStream(i, OUTLET)->MassFlow()->GetValue(); }
		}
		if (UnknownFmass != 0){ UnknownFmass->SetValue(flowdir*sumF); }
		massflowpassed = true;
	}
	if (nmassspecced == nin + nout)
	{
		//if all known assume solved this part
		massflowpassed = true;
	}

	if (nmolspecced == nin + nout)
	{
		//if all known assume solved this part
		molflowpassed = true;
	}


	//if  ninlets>1, do compbalance.
	//all outlet streams are 1 dof
	//inlet streams are 1 dof each
	//if 1 inlet I only need 1 composition
	// if 1+ inlets then i need (nin+nout-1) compositions
	nspecced = 0;
	
	//check who has a composition
	int ncomps = _parent->GetStream(0, INLET)->NComps();
	X = new double[ncomps];
	for (int i = 0; i < nin; i++)
	{
		if (_parent->GetStream(i, INLET)->Composition()->IsKnown() && _parent->GetStream(i, INLET)->MolarFlow()->IsKnown())
		{
			nspecced++;
			X = _parent->GetStream(i, INLET)->Composition()->GetValues();
			cout << X[0] << "\n";
			cout << X[1] << "\n";
			cout << X[2] << "\n";
		}
		else
		{
			flowdir = -1;
			UnknownX = _parent->GetStream(i, INLET);
		}

	}

	for (int i = 0; i < nout; i++)
	{
		if (_parent->GetStream(i, OUTLET)->Composition()->IsKnown() && _parent->GetStream(i, OUTLET)->MolarFlow()->IsKnown())
		{
			nspecced++;
			X = _parent->GetStream(i, OUTLET)->Composition()->GetValues();
		}
		else
		{
			flowdir = 1;
			UnknownX = _parent->GetStream(i, OUTLET);
		}
	}

	bool cansolvecomps = false;
	double moles = 0;
	
	if (nout == 1)
	{
		
		if (nspecced == (nin + nout - 1))
		{
			cansolvecomps = true;
			//sum up moles
			for (int j = 0; j < ncomps; j++)
			{
				moles = 0;
				for (int i = 0; i < nin; i++)
				{
					if (_parent->GetStream(i, INLET)->Composition()->IsKnown())
					{
						moles = moles + _parent->GetStream(i, INLET)->Composition()->GetValue(j) * _parent->GetStream(i, INLET)->MolarFlow()->GetValue();
					}

				}
				for (int i = 0; i < nout; i++)
				{
					if (_parent->GetStream(i, OUTLET)->Composition()->IsKnown())
					{
						moles = moles - _parent->GetStream(i, OUTLET)->Composition()->GetValue(j) * _parent->GetStream(i, OUTLET)->MolarFlow()->GetValue();
					}
				}
				
				X[j] = moles * flowdir / UnknownX->MolarFlow()->GetValue();
				cout << X[j] << "\n";

			}
			UnknownX->Composition()->SetValues(ncomps, X);
			comppassed = true;
		}
	}
	else
	{
		if (nspecced <(nin + nout))
		{
			cansolvecomps = true;
			for (int i = 0; i < nin; i++)
			{
				if (!_parent->GetStream(i, INLET)->Composition()->IsKnown())
				{
					_parent->GetStream(i, INLET)->Composition()->SetValues(ncomps, X);

				}

			}

			for (int i = 0; i < nout; i++)
			{
				if (!_parent->GetStream(i, OUTLET)->Composition()->IsKnown())
				{
					_parent->GetStream(i, OUTLET)->Composition()->SetValues(ncomps, X);
				}
			}

			comppassed = true;
		}
	}
	if (nspecced == (nin + nout))
	{
		comppassed = true;
	}

passcompositions:




	if (comppassed&&massflowpassed&&molflowpassed)
	{
		return true;
	}
	else
	{
		return false;
	}

}


ComponentBalance::ComponentBalance()
{
}


ComponentBalance::~ComponentBalance()
{
}
