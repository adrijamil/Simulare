#pragma once
#include "PropertyCalc.h"
#include "Stream.h"
#include "PropPack.h"

class MolWtCalc :
	public PropertyCalc
{
public:
	void Calculate();
	
	MolWtCalc();
	~MolWtCalc();
private:
	void CalcFluid();
};


