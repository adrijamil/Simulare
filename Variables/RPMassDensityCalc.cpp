#include "stdafx.h"
#include "RPMassDensityCalc.h"


RPMassDensityCalc::RPMassDensityCalc()
{
}


RPMassDensityCalc::~RPMassDensityCalc()
{
}
void RPMassDensityCalc::Calculate()
{
	double massd;
	for (int i = 0; i < 3; i++)
	{
		if (_parent->RefStream()->Phases[i].MolarDensity != -32767)
		{
			_parent->RefStream()->Phases[i].MassDensity = _parent->RefStream()->Phases[i].MolarDensity*_parent->RefStream()->Phases[i].MolecularWeight / 1000;
		}
	}
}