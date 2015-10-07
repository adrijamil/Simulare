#pragma once
#include "UnitOp.h"
#include "Stream.h"
class Splitter:
	public UnitOp
{
public:
	RealVariable* SplitFractions(){ return _splitfractions; }
	Splitter();
	Splitter(string name);
	void Output(){};// later show something like pressure drop
	~Splitter();
private:
	RealVariable* _splitfractions= new RealVariable; //default by mol;
};