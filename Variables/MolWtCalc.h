#pragma once
#include "PropertyCalc.h"
#include "Stream.h"
#include "PropPack.h"

class MolWtCalc :
	public PropertyCalc
{
public:
	bool Calculate();
	
	MolWtCalc();
	~MolWtCalc();
private:
	void CalcFluid();
};


