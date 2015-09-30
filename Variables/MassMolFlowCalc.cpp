#include "stdafx.h"
#include "MassMolFlowCalc.h"


MassMolFlowCalc::MassMolFlowCalc()
{
}


MassMolFlowCalc::~MassMolFlowCalc()
{
}

void MassMolFlowCalc::Calculate(Stream* thestream)
{
	CalcFluid(thestream);
	CalcFluid(thestream->Phases(0));
	CalcFluid(thestream->Phases(1));
}



void MassMolFlowCalc::CalcFluid(Fluid* thefluid)
{
	// if mass flow is known, convert to mol
	// else convert mol to mass
	double fmass, fmol;
	if (thefluid->MassFlow()->IsKnown())
	{
		fmol = thefluid->MassFlow()->GetValue() / thefluid->MolecularWeight()->GetValue();
		thefluid->MolarFlow()->SetValue(fmol);
	}
	else if (thefluid->MolarFlow()->IsKnown())
	{
		fmass = thefluid->MolarFlow()->GetValue()  * thefluid->MolecularWeight()->GetValue();
		thefluid->MassFlow()->SetValue(fmass);
	}
}