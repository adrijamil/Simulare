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
	_is_known = true;
	_setvalue(thevalue);
}

void RealVariable::SetValue(int i, double thevalue)
{
	_setvalue(i,thevalue);
	_is_known = true;
}

void RealVariable::SetValues(int N, double* thevalue)
{
	_setvalues(N, thevalue);
	_is_known = true;
}