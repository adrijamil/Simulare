#include "stdafx.h"
#include "StreamCalc.h"
#include "Stream.h"

StreamCalc::StreamCalc()
{
}


bool StreamCalc::Solve()
{
	bool retval;

	_refstream->GetPropertyPackage()->RefStream()->ReadStream(_refstream);
	retval = _propertycalc->Solve();
	return retval;

}

StreamCalc::~StreamCalc()
{
}
