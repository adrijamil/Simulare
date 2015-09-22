#pragma once
#include "PropertyCalc.h"
#include "Stream.h"
#include "PropPack.h"

class MolWtCalc :
	public PropertyCalc
{
public:
	void Calculate(Stream* thestream);
	
	MolWtCalc();
	~MolWtCalc();
private:
	void CalcFluid(Fluid* thefluid);
};


