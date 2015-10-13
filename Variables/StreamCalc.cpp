#include "stdafx.h"
#include "StreamCalc.h"
#include "Stream.h"

StreamCalc::StreamCalc()
{

}




void StreamCalc::Setup(PropertyCalc* thePC, Stream* theRS)
{
	RealVariable** myvariables;
	_propertycalc = thePC;
	_refstream = theRS;

	myvariables = _propertycalc->GetVariables(_refstream);

	int nvar = sizeof(*myvariables) / sizeof(myvariables);
	cout << nvar;

	for (int i = 0; i < nvar; i++)
	{
		AddVariable(myvariables[i]);
	}
}

bool StreamCalc::Solve()
{
	bool retval;

	_refstream->GetPropertyPackage()->RefStream()->ReadStream(_refstream);
	//_propertycalc.getvariables()//this should return all variables to map to the stackobject
	retval = _propertycalc->Solve();
	return retval;

}

StreamCalc::~StreamCalc()
{
}
