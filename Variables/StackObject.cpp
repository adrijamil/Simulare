#include "stdafx.h"
#include "StackObject.h"


StackObject::StackObject()
{
}


StackObject::~StackObject()
{
}

void StackObject::AddVariable(RealVariable* thevar)
{
	_nvariables++;
	_variables = (RealVariable**)realloc(_variables, _nvariables* sizeof(*thevar)); //allocate new array

	if (_variables != NULL) //if it's null then realloc tak jadi//means theres only one guy;
	{
		_variables[_nvariables - 1] = &(*thevar);
	}
}

double StackObject::FractionKnown()//
{
	double retval;
	double nknown=0;

	for (int i = 0; i < _nvariables; i++)
	{
		if (_variables[i]->IsKnown())
		{
			nknown = nknown + 1;
		}
	}
	retval = nknown / _nvariables;
	return retval;
}