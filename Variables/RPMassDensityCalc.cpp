#include "stdafx.h"
#include "RPMassDensityCalc.h"


RPMassDensityCalc::RPMassDensityCalc()
{
}


RPMassDensityCalc::~RPMassDensityCalc()
{
}
bool RPMassDensityCalc::Calculate()
{
	bool retval = true;
	double massd;
	for (int i = 0; i < 3; i++)
	{
		if (_parent->RefStream()->Phases[i].MolarDensity != -32767)
		{
			_parent->RefStream()->Phases[i].MassDensity = _parent->RefStream()->Phases[i].MolarDensity*_parent->RefStream()->Phases[i].MolecularWeight / 1000;
		}
		else if(_parent->RefStream()->Phases[i].MassDensity==-32767)
		{
			retval = false;
		}
	}

	return retval;
}