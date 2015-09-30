#include "stdafx.h"
#include "ComponentBalance.h"
#include "UnitOp.h"
#include "Stream.h"

bool ComponentBalance::Solve()
{
	//check DOF
	//Solve if can
	//do by molar flow first - 
	//if I have n streams, n-1 streams need to be known;
	int nspecced = 0;
	int nin, nout;
	nin = _parent->NInlets();
	nout = _parent->NOutlets();
	RealVariable* UnknownF=0;
	RealVariable* KnownX = 0;
	double sumF = 0;
	double* X;
	bool flowpassed = false;
	bool comppassed = false;

	for (int i = 0; i < nin; i++)
	{
		if (_parent->GetStream(i, INLET)->MolarFlow()->IsKnown())
		{
			nspecced++;
		}
		else
		{
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
			UnknownF = _parent->GetStream(i, INLET)->MolarFlow();
		}
	}

	if (nspecced + 1 == nin + nout)//DOF is 0
	{
		for (int i = 0; i < nin; i++)
		{
			sumF = sumF + _parent->GetStream(i, INLET)->MolarFlow()->GetValue();
		}
		for (int i = 0; i < nout; i++)
		{
			sumF = sumF - _parent->GetStream(i, OUTLET)->MolarFlow()->GetValue();
		}
		if (UnknownF != 0){ UnknownF->SetValue(sumF); }
		flowpassed = true;
	}
	else if (nspecced == nin + nout)
	{
		//if all known assume solved this part
		flowpassed = true;
	}

	//check who has a composition
	int ncomps = _parent->GetStream(0, INLET)->NComps();
	for (int i = 0; i < nin; i++)
	{
		if (_parent->GetStream(i, INLET)->Composition()->IsKnown())
		{
			X = _parent->GetStream(i, INLET)->Composition()->GetValues();
			goto passcompositions;
		}
		
	}

	for (int i = 0; i < nout; i++)
	{
		if (_parent->GetStream(i, OUTLET)->Composition()->IsKnown())
		{
			X = _parent->GetStream(i, INLET)->Composition()->GetValues();
			goto passcompositions;
		}
	}

	return false; //if you get here then cannot pass compositions yet;

passcompositions:
	for (int i = 0; i < nin; i++)
	{
		if (!_parent->GetStream(i, INLET)->Composition()->IsKnown())
		{
			_parent->GetStream(i, INLET)->Composition()->SetValues(ncomps,X);

		}

	}

	for (int i = 0; i < nout; i++)
	{
		if (!_parent->GetStream(i, OUTLET)->Composition()->IsKnown())
		{
			_parent->GetStream(i, INLET)->Composition()->SetValues(ncomps, X);
		}
	}
	comppassed = true;
	
	return true;
}



ComponentBalance::ComponentBalance()
{
}


ComponentBalance::~ComponentBalance()
{
}
