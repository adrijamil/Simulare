#include "stdafx.h"
#include "RPMassDensityCalc.h"


RPMassDensityCalc::RPMassDensityCalc()
{
}

RealVariable**  RPMassDensityCalc::GetVariables(Stream* refstream)
{
	RealVariable** thevars = new RealVariable*[9];

	thevars[0] = refstream->MassDensity();
	thevars[1] = refstream->MolarDensity();
	thevars[2] = refstream->MolecularWeight();

	thevars[3] = refstream->Phases(0)->MassDensity();
	thevars[4] = refstream->Phases(0)->MolarDensity();
	thevars[5] = refstream->Phases(0)->MolecularWeight();

	thevars[6] = refstream->Phases(1)->MassDensity();
	thevars[7] = refstream->Phases(1)->MolarDensity();
	thevars[8] = refstream->Phases(1)->MolecularWeight();

	return thevars;
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