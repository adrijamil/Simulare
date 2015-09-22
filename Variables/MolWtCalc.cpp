#include "stdafx.h"
#include "MolWtCalc.h"


MolWtCalc::MolWtCalc()
{
}

void MolWtCalc::Calculate(Stream* thestream)
{
	Fluid* somefluid;

	CalcFluid(thestream);
	CalcFluid(thestream->Phases(0));
	CalcFluid(thestream->Phases(1));

}

MolWtCalc::~MolWtCalc()
{
}

void MolWtCalc::CalcFluid(Fluid* thefluid)
{
	int ncomps= _parent->NComps();
	double theMw;
	theMw = 0;

	for (int i = 0; i < ncomps; i++)
	{
		theMw = theMw + (thefluid->Composition()->GetValue(i))*_parent->GetComponent(i).Mw;
	}
	thefluid->MolecularWeight()->SetValue(theMw);

}