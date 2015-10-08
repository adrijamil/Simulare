#include "stdafx.h"
#include "MassMolFlowCalc.h"


MassMolFlowCalc::MassMolFlowCalc()
{
}



bool MassMolFlowCalc::Calculate()
{
	double fmass, fmol;
	bool retval=true;
	for (int i = 0; i < 3; i++)
	{
		//cout << _parent->RefStream()->Phases[i].MassFlow << "\n";
		//cout << _parent->RefStream()->Phases[i].MolarFlow << "\n";

		if (_parent->RefStream()->Phases[i].MassFlow != -32767 && _parent->RefStream()->Phases[i].MolecularWeight != -32767)
		{
			fmol = _parent->RefStream()->Phases[i].MassFlow / _parent->RefStream()->Phases[i].MolecularWeight;
			_parent->RefStream()->Phases[i].MolarFlow = fmol;
		}
		else if (_parent->RefStream()->Phases[i].MolarFlow != -32767 && _parent->RefStream()->Phases[i].MolecularWeight != -32767)
		{
			fmass = _parent->RefStream()->Phases[i].MolarFlow * _parent->RefStream()->Phases[i].MolecularWeight;
			_parent->RefStream()->Phases[i].MassFlow = fmass;
		}
		else if (_parent->RefStream()->Phases[i].MolarFlow == -32767 && _parent->RefStream()->VapourFraction != -32767)
		{
			if (i == 1)
			{
				fmol = _parent->RefStream()->Phases[0].MolarFlow * _parent->RefStream()->VapourFraction;
				_parent->RefStream()->Phases[i].MolarFlow = fmol;
				fmass = fmol* _parent->RefStream()->Phases[i].MolecularWeight;
				_parent->RefStream()->Phases[i].MassFlow = fmass;
			}
			else if (i == 2)
			{
				fmol = _parent->RefStream()->Phases[0].MolarFlow *(1- _parent->RefStream()->VapourFraction);
				_parent->RefStream()->Phases[i].MolarFlow = fmol;
				fmass = fmol* _parent->RefStream()->Phases[i].MolecularWeight;
				_parent->RefStream()->Phases[i].MassFlow = fmass;
			}
		}
		else if (_parent->RefStream()->Phases[i].MolarFlow == -32767 && _parent->RefStream()->Phases[i].MassFlow == -32767)
		{
			retval = false;
		}
		
	}
	return retval;
}

MassMolFlowCalc::~MassMolFlowCalc()
{
}
