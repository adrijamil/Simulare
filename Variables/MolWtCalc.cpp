#include "stdafx.h"
#include "MolWtCalc.h"


MolWtCalc::MolWtCalc()
{
}

bool MolWtCalc::Calculate()
{
	int ncomps = _parent->NComps();
	double theMw;
	bool retval = true;

	for (int k = 0; k < 3; k++)
	{
		theMw = 0;
		if (_parent->RefStream()->Phases[k].Composition[0] != -32767)
		{
			for (int i = 0; i < ncomps; i++)
			{
				theMw = theMw + (_parent->RefStream()->Phases[k].Composition[i] * _parent->GetComponent(i).Mw);
			}
			_parent->RefStream()->Phases[k].MolecularWeight = theMw;
		}
		else if (_parent->RefStream()->Phases[k].Composition[0] == -32767 && _parent->RefStream()->Phases[k].MolecularWeight==-32767)
		{
			retval = false;
		}
	}
	return retval;
}

MolWtCalc::~MolWtCalc()
{
}

void MolWtCalc::CalcFluid()
{

	/*for (int i = 0; i < ncomps; i++)
	{
		theMw = theMw + (thefluid->Composition()->GetValue(i))*_parent->GetComponent(i).Mw;
	}
	thefluid->MolecularWeight()->SetValue(theMw);
*/
}