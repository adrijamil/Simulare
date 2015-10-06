#include "stdafx.h"
#include "MolWtCalc.h"


MolWtCalc::MolWtCalc()
{
}

void MolWtCalc::Calculate()
{
	int ncomps = _parent->NComps();
	double theMw;

	for (int k = 0; k < ncomps; k++)
	{
		theMw = 0;
		for (int i = 0; i < ncomps; i++)
		{
			theMw = theMw + (_parent->RefStream()->Phases[k].Composition[i] * _parent->GetComponent(i).Mw);
		}
		_parent->RefStream()->Phases[k].MolecularWeight = theMw;
	}
}

MolWtCalc::~MolWtCalc()
{
}

void MolWtCalc::CalcFluid()
{
	int ncomps= _parent->NComps();
	double theMw;
	theMw = 0;

	/*for (int i = 0; i < ncomps; i++)
	{
		theMw = theMw + (thefluid->Composition()->GetValue(i))*_parent->GetComponent(i).Mw;
	}
	thefluid->MolecularWeight()->SetValue(theMw);
*/
}