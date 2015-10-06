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
	int nin, nout;
	nin = _parent->NInlets();
	nout = _parent->NOutlets();
	RealVariable* UnknownF = 0;
	RealVariable* KnownX = 0;
	Stream* UnknownX = 0;
	double sumF = 0;
	double* X;
	bool flowpassed = false;
	bool comppassed = false;
	int flowdir;

	for (int i = 0; i < nin; i++)
	{
		if (_parent->GetStream(i, INLET)->MolarFlow()->IsKnown())
		{
			nspecced++;
		}
		else
		{
			flowdir = -1;
			UnknownF = _parent->GetStream(i, INLET)->MolarFlow();
		}
	}

	for (int i = 0; i < nout; i++)
	{
		if (_parent->GetStream(i, OUTLET)->MolarFlow()->IsKnown())
		{
			nspecced++;
		}
		else
		{
			flowdir = 1;
			UnknownF = _parent->GetStream(i, OUTLET)->MolarFlow();
		}
	}

	if (nspecced + 1 == nin + nout)//DOF is 0
	{
		for (int i = 0; i < nin; i++)
		{
			if (_parent->GetStream(i, INLET)->MolarFlow()->IsKnown()){ sumF = sumF + _parent->GetStream(i, INLET)->MolarFlow()->GetValue(); }
		}
		for (int i = 0; i < nout; i++)
		{
			if (_parent->GetStream(i, OUTLET)->MolarFlow()->IsKnown()){ sumF = sumF - _parent->GetStream(i, OUTLET)->MolarFlow()->GetValue(); }
		}
		if (UnknownF != 0){ UnknownF->SetValue(flowdir*sumF); }
		flowpassed = true;
	}
	else if (nspecced == nin + nout)
	{
		//if all known assume solved this part
		flowpassed = true;
	}
	else
	{
		return false;
	}

	//if  ninlets>1, do compbalance.
	//all outlet streams are 1 dof
	//inlet streams are 1 dof each
	//if 1 inlet I only need 1 composition
	// if 1+ inlets then i need (nin+nout-1) compositions
	nspecced = 0;

	//check who has a composition
	int ncomps = _parent->GetStream(0, INLET)->NComps();
	for (int i = 0; i < nin; i++)
	{
		if (_parent->GetStream(i, INLET)->Composition()->IsKnown())
		{
			nspecced++;
			X = _parent->GetStream(i, INLET)->Composition()->GetValues();
		}
		else
		{
			flowdir = -1;
			UnknownX = _parent->GetStream(i, INLET);
		}

	}

	for (int i = 0; i < nout; i++)
	{
		if (_parent->GetStream(i, OUTLET)->Composition()->IsKnown())
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
	X = new double[ncomps];
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
				cout << "\n" << X[j];
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


passcompositions:




	if (comppassed&&flowpassed)
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
