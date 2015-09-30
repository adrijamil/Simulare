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
bool HeatBalance::Solve()
{
	//check DOF
	//Solve if can
	//do by molar flow first - 
	//if I have n streams, n-1 streams need to be known;
	int nspecced = 0;
	int nin, nout;
	nin = _parent->NInlets();
	nout = _parent->NOutlets();
	Stream* UnknownStrm = 0;
	RealVariable* KnownX = 0;
	double sumH = 0;
	double* X;
	bool enthalpypassed = false;
	bool comppassed = false;

	//all flows need to be known
	for (int i = 0; i < nin; i++)
	{
		if (!_parent->GetStream(i, INLET)->MolarFlow()->IsKnown())
		{
			return false;
		}
	}

	for (int i = 0; i < nout; i++)
	{
		if (!_parent->GetStream(i, OUTLET)->MolarFlow()->IsKnown())
		{
			return false;
		}
	}

	//check enthalpies
	for (int i = 0; i < nin; i++)
	{
		if (_parent->GetStream(i, INLET)->MolarEnthalpy()->IsKnown())
		{
			nspecced++;
		}
		else
		{
			UnknownStrm = _parent->GetStream(i, INLET);
		}
	}

	for (int i = 0; i < nout; i++)
	{
		if (_parent->GetStream(i, OUTLET)->MolarEnthalpy()->IsKnown())
		{
			nspecced++;
		}
		else
		{
			UnknownStrm = _parent->GetStream(i, OUTLET);
		}
	}

	if (nspecced + 1 == nin + nout)//DOF is 0
	{
		for (int i = 0; i < nin; i++)
		{
			if (UnknownStrm != _parent->GetStream(i, INLET))
			{
				sumH = sumH + _parent->GetStream(i, INLET)->MolarFlow()->GetValue()*_parent->GetStream(i, INLET)->MolarEnthalpy()->GetValue();
			}
			
		}
		for (int i = 0; i < nout; i++)
		{
			if (UnknownStrm != _parent->GetStream(i, OUTLET))
			{
				sumH = sumH + _parent->GetStream(i, OUTLET)->MolarFlow()->GetValue()*_parent->GetStream(i, OUTLET)->MolarEnthalpy()->GetValue();
			}
		}
		if (_heatinput != 0){ sumH = sumH + _heatinput->GetValue(); }
		if (UnknownStrm != 0)
		{ 
			sumH = sumH / UnknownStrm->MolarFlow()->GetValue();
			UnknownStrm->MolarEnthalpy()->SetValue(sumH);
		}
		enthalpypassed = true;
	}
	else if (nspecced == nin + nout)
	{
		//if all known assume solved this part
		enthalpypassed = true;
	}

	return true;
}