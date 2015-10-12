#pragma once
#include "RealVariable.h"


class StackObject
{
public:
	StackObject();
	~StackObject();
	virtual bool Solve()=0;
private:
	RealVariable* _variables;
};

