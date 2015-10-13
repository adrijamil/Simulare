#pragma once
#include "RealVariable.h"


class StackObject
{
public:
	StackObject();
	~StackObject();
	virtual bool Solve()=0;
	void AddVariable(RealVariable* _variables);
	bool IsDirty(){ return _isdirty; }
	double FractionKnown();//
	virtual string Name(){ return 0; };
	bool DependsOn(StackObject* theStackObject)
	{
		//if any of this _variables are calculated by theStackObject
		for (int i = 0; i < _nvariables; i++)
		{
			if (_variables[i]->CalculatedBy() == theStackObject)
			{
				return true;
			}
		}
		return false;
	}
//
protected:
	RealVariable** _variables;
	int  _nvariables=0;

	bool _isdirty = true;
};

