#include "stdafx.h"
#include "MolWtCalc.h"


MolWtCalc::MolWtCalc()
{
}

void MolWtCalc::Calculate()
{
	int ncomps = _parent->NComps();
	double theMw;
	theMw = 0;

	for (int i = 0; i < ncomps; i++)
	{
	theMw = theMw + (_parent->RefStream()->Liquid.Composition[i]*_parent->GetComponent(i).Mw);
	}
	_parent->RefStream()->Liquid.MolecularWeight = theMw;

	theMw = 0;
	for (int i = 0; i < ncomps; i++)
	{
		theMw = theMw + (_parent->RefStream()->Vapour.Composition[i] * _parent->GetComponent(i).Mw);
	}
	_parent->RefStream()->Vapour.MolecularWeight = theMw;

	theMw = 0;
	for (int i = 0; i < ncomps; i++)
	{
		theMw = theMw + (_parent->RefStream()->Overall.Composition[i] * _parent->GetComponent(i).Mw);
	}
	_parent->RefStream()->Overall.MolecularWeight = theMw;

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