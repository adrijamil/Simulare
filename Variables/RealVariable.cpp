#include "stdafx.h"
#include "RealVariable.h"

RealVariable::RealVariable()
{
}

RealVariable::~RealVariable()
{
}

void RealVariable::SetValue(double thevalue)
{
	if (thevalue!=-32767)
	{
		_is_known = true;
		_setvalue(thevalue);
	}
}

void RealVariable::SetValue(int i, double thevalue)
{
	if (thevalue != -32767)
	{
		_setvalue(i, thevalue);
		_is_known = true;
	}
}

void RealVariable::SetValues(int N, double* thevalue)
{
	if (thevalue[0] != -32767)
	{
		_setvalues(N, thevalue);
		_is_known = true;
	}
}