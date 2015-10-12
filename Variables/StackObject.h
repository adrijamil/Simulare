#pragma once
#include "RealVariable.h"


class StackObject
{
public:
	StackObject();
	~StackObject();
	virtual bool Solve()=0;
	void AddVariable(RealVariable* _variables){};
	bool IsDirty(){ return _isdirty; }
private:
	RealVariable* _variables;
	bool _isdirty = false;
};

