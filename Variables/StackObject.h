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
	double FractionKnown(){ return -32767; }//
	bool DependsOn(StackObject* theStackObject)
	{
		//if any of this _variables are calculated by theStackObject
		return false;
	}
//
private:
	RealVariable* _variables;
	bool _isdirty = false;
};

