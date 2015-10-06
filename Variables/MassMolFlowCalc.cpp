#include "stdafx.h"
#include "MassMolFlowCalc.h"


MassMolFlowCalc::MassMolFlowCalc()
{
}



void MassMolFlowCalc::Calculate()
{
	double fmass, fmol;
	
	for (int i = 0; i < 3; i++)
	{
		if (_parent->RefStream()->Phases[i].MassFlow != -32767)
		{
			fmol = _parent->RefStream()->Phases[i].MassFlow / _parent->RefStream()->Phases[i].MolecularWeight;
			_parent->RefStream()->Phases[i].MolarFlow = fmol;
		}
		else if (_parent->RefStream()->Phases[i].MolarFlow != -32767)
		{
			fmass = _parent->RefStream()->Phases[i].MolarFlow * _parent->RefStream()->Phases[i].MolecularWeight;
			_parent->RefStream()->Phases[0].MassFlow = fmass;
		}
	}
}

MassMolFlowCalc::~MassMolFlowCalc()
{
}
