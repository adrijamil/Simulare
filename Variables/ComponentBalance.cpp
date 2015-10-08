#include "stdafx.h"
#include "ComponentBalance.h"
#include "UnitOp.h"
#include "Stream.h"

bool ComponentBalance::_altsolve()
{
	int nin, nout;
	nin = _parent->NInlets();
	nout = _parent->NOutlets();
	int nmassspecced = 0;
	int nmolspecced = 0;
	int nxspecced = 0;
	bool flowpassed = false;
	bool comppassed = false;
	double sumMol = 0;
	double sumMass = 0;
	Stream* UnknownX = 0;
	double* X;
	RealVariable* UnknownFmol = 0;
	RealVariable* UnknownFmass = 0;
	RealVariable* KnownX = 0;
	int massflowdir = 0;
	int molflowdir = 0;
	int Xdir = 0;
	double moles = 0;
	//check mole flows
	int ncomps = _parent->GetStream(0, INLET)->NComps();
	X = new double[ncomps];
	for (int i = 0; i < nin; i++)
	{
		if (_parent->GetStream(i, INLET)->MolarFlow()->IsKnown())
		{
			nmolspecced++;
			sumMol = sumMol + _parent->GetStream(i, INLET)->MolarFlow()->GetValue();
		}
		else
		{
			molflowdir = -1;
			UnknownFmol = _parent->GetStream(i, INLET)->MolarFlow();
		}
	}

	for (int i = 0; i < nout; i++)
	{
		if (_parent->GetStream(i, OUTLET)->MolarFlow()->IsKnown())
		{
			nmolspecced++;
			sumMol = sumMol - _parent->GetStream(i, OUTLET)->MolarFlow()->GetValue();
		}
		else
		{
			molflowdir = 1;
			UnknownFmol = _parent->GetStream(i, OUTLET)->MolarFlow();
		}
	}


	//check mass flows
	for (int i = 0; i < nin; i++)
	{
		if (_parent->GetStream(i, INLET)->MassFlow()->IsKnown())
		{
			nmassspecced++;
			sumMass = sumMass + _parent->GetStream(i, INLET)->MassFlow()->GetValue();
		}
		else
		{
			massflowdir = -1;
			UnknownFmass = _parent->GetStream(i, INLET)->MassFlow();
		}
	}

	for (int i = 0; i < nout; i++)
	{
		if (_parent->GetStream(i, OUTLET)->MassFlow()->IsKnown())
		{
			nmassspecced++;
			sumMass = sumMass - _parent->GetStream(i, OUTLET)->MassFlow()->GetValue();
		}
		else
		{
			massflowdir = 1;
			UnknownFmass = _parent->GetStream(i, OUTLET)->MassFlow();
		}
	}

	//check composition
	for (int i = 0; i < nin; i++)
	{
		if (_parent->GetStream(i, INLET)->Composition()->IsKnown())
		{
			nxspecced++;
			KnownX = _parent->GetStream(i, INLET)->Composition();
		}
		else
		{
			Xdir = -1;
			UnknownX = _parent->GetStream(i, INLET);
		}

	}

	for (int i = 0; i < nout; i++)
	{
		if (_parent->GetStream(i, OUTLET)->Composition()->IsKnown())
		{
			nxspecced++;
			KnownX = _parent->GetStream(i, OUTLET)->Composition();
		}
		else
		{
			Xdir = 1;
			UnknownX = _parent->GetStream(i, OUTLET);
		}
	}

	if (nin == 1 && nout == 1) //valve, heater, compressor etc
	{
		if (nmassspecced == 1) //either pass mass or mole flow
		{
			UnknownFmass->SetValue(massflowdir*sumMass);
			flowpassed = true;
		}
		else if (nmolspecced==1)
		{
			UnknownFmol->SetValue(molflowdir*sumMol);
			flowpassed = true;
		}
		else if (nmolspecced - nin - nout == 0 || nmolspecced - nin - nout == 0)
		{
			flowpassed = true;
		}

		if (KnownX != 0 && UnknownX != 0)
		{
			for (int j = 0; j < ncomps; j++)
			{
				X[j] = KnownX->GetValue(j);
			}
			UnknownX->Composition()->SetValues(ncomps, X);
			comppassed = true;
		}
		else if (nxspecced - nin - nout == 0)
		{
			comppassed = true;
		}
		
	}
	else if (nin == 1)
	{
		if (nmassspecced-nin-nout == 1) //either pass mass or mole flow
		{
			UnknownFmass->SetValue(massflowdir*sumMass);
			flowpassed = true;
		}
		else if (nmolspecced - nin - nout == 1)
		{
			UnknownFmol->SetValue(molflowdir*sumMol);
			nmolspecced++;
			flowpassed = true;
		}
		else if (nmolspecced - nin - nout == 0 || nmolspecced - nin - nout == 0)
		{
			flowpassed = true;
		}

		if (nxspecced - nin - nout == 1 && nmolspecced - nin + nout == 0 && KnownX != 0)//all flows known, all but on comp known
		{
			for (int j = 0; j < ncomps; j++)
			{
				for (int i = 0; i < nin; i++)
				{
					if (UnknownX != _parent->GetStream(i, INLET))
					{
						moles = moles + _parent->GetStream(i, INLET)->Composition()->GetValue(j) * _parent->GetStream(i, INLET)->MolarFlow()->GetValue();
					}
				}
				for (int i = 0; i < nout; i++)
				{
					if (UnknownX != _parent->GetStream(i, OUTLET))
					{
						moles = moles - _parent->GetStream(i, OUTLET)->Composition()->GetValue(j) * _parent->GetStream(i, OUTLET)->MolarFlow()->GetValue();
					}
				}
				X[j] = moles * Xdir / UnknownX->MolarFlow()->GetValue();
				cout << X[j] << "\n";
			}
			UnknownX->Composition()->SetValues(ncomps, X);
			comppassed = true;
		}//end if
	}
	else if (nout == 1)
	{
		if (nmassspecced - nin - nout == 1) //either pass mass or mole flow
		{
			UnknownFmass->SetValue(massflowdir*sumMass);
			flowpassed = true;
		}
		else if (nmolspecced - nin - nout == 1)
		{
			UnknownFmol->SetValue(molflowdir*sumMol);
			nmolspecced++;
			flowpassed = true;
		}
		else if (nmolspecced - nin - nout == 0 || nmolspecced - nin - nout == 0)
		{
			flowpassed = true;
		}
		if (nxspecced == 1 && nmolspecced - nin + nout == 0)
		{
			if (KnownX != 0)
			{
				for (int j = 0; j < ncomps; j++)
				{
					X[j] = KnownX->GetValue(j);
				}
				UnknownX->Composition()->SetValues(ncomps, X);
				comppassed = true;
			}
		}
	}

	if (flowpassed &&comppassed)
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool ComponentBalance::Solve()
{
	//check DOF
	//Solve if can
	//do by molar flow first - 

	bool dabool = _altsolve();
	return dabool;

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
			KnownX = _parent->GetStream(i, INLET)->Composition();
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
			KnownX = _parent->GetStream(i, OUTLET)->Composition();
		}
		else
		{
			flowdir = 1;
			UnknownX = _parent->GetStream(i, OUTLET);
		}
	}

	bool cansolvecomps = false;
	double moles = 0;
	
	if (nout == 1 && nspecced == (nin + nout - 1))
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
	else if (nout == 1 && nin == 1)
	{
		for (int j = 0; j < ncomps; j++)
		{
			X[j] = KnownX->GetValue(j);
		}
		UnknownX->Composition()->SetValues(ncomps, X);
	}
	else if(nspecced <(nin + nout))
	{
		cansolvecomps = true;
		for (int i = 0; i < nin; i++)
		{
			if (!_parent->GetStream(i, INLET)->Composition()->IsKnown())
			{
				_parent->GetStream(i, INLET)->Composition()->SetValues(ncomps, KnownX->GetValues());

			}

		}

		for (int i = 0; i < nout; i++)
		{
			if (!_parent->GetStream(i, OUTLET)->Composition()->IsKnown())
			{
				_parent->GetStream(i, OUTLET)->Composition()->SetValues(ncomps, KnownX->GetValues());
			}
		}

		comppassed = true;
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
