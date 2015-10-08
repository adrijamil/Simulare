#include "stdafx.h"
#include "MassMolFlowCalc.h"


MassMolFlowCalc::MassMolFlowCalc()
{
}



bool MassMolFlowCalc::Calculate()
{
	double fmass, fmol;
	bool retval = true;

	//do overall
	fwStream* thefw = _parent->RefStream();
	int i = 0;
	//if dunno mass try calc
	if (thefw->Phases[i].MassFlow == -32767)
	{
		if (thefw->Phases[i].MolarFlow != -32767)
		{
			if (thefw->Phases[i].MolecularWeight != -32767)
			{
				fmass = thefw->Phases[i].MolarFlow * thefw->Phases[i].MolecularWeight;
				thefw->Phases[i].MassFlow = fmass;
			}
		}
	}
	if (thefw->Phases[i].MassFlow == -32767)
	{
		retval = false;
	}

	//if dunno molar flow then calc;
	if (thefw->Phases[i].MolarFlow == -32767)
	{
		if (thefw->Phases[i].MassFlow != -32767)
		{
			if (thefw->Phases[i].MolecularWeight != -32767)
			{
				fmol = thefw->Phases[i].MassFlow / thefw->Phases[i].MolecularWeight;
				thefw->Phases[i].MolarFlow = fmol;
			}
		}
	}
	if (thefw->Phases[i].MolarFlow == -32767)
	{
		retval = false;
	}

	//do gas and liquid
	for (int i = 1; i < 3; i++)
	{
		//try mol first
		if (thefw->Phases[i].MolarFlow == -32767)
		{
			//try get from mass flow and molecular weight
			if (thefw->Phases[i].MassFlow != -32767)
			{
				if (thefw->Phases[i].MolecularWeight != -32767)
				{
					fmol = thefw->Phases[i].MassFlow / thefw->Phases[i].MolecularWeight;
					thefw->Phases[i].MolarFlow = fmol;
				}
			}
			else if (thefw->VapourFraction != -32767&&thefw->Phases[0].MolarFlow!=-32767)
			{
				if (i == 1)
				{
					fmol = thefw->Phases[0].MolarFlow*thefw->VapourFraction;
				}
				else
				{
					fmol = thefw->Phases[0].MolarFlow*(1 - thefw->VapourFraction);
				}
				thefw->Phases[i].MolarFlow = fmol;
			}

		}
		if (thefw->Phases[i].MolarFlow == -32767)
		{
			retval = false;
		}
		//then try mass flow
		if (thefw->Phases[i].MassFlow == -32767)
		{
			if (thefw->Phases[i].MolarFlow != -32767)
			{
				if (thefw->Phases[i].MolecularWeight != -32767)
				{
					fmass = thefw->Phases[i].MolarFlow * thefw->Phases[i].MolecularWeight;
					thefw->Phases[i].MassFlow = fmass;
				}
			}
		}
		if (thefw->Phases[i].MassFlow == -32767)
		{
			retval = false;
		}
	}
	return retval;
}

MassMolFlowCalc::~MassMolFlowCalc()
{
}
