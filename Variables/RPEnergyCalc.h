#pragma once
#include "PropertyCalc.h"
#include "Stream.h"
#include "RefPropPack.h" 
#include <windows.h>

class RPEnergyCalc :
	public PropertyCalc
{
public:
	RPEnergyCalc();
	~RPEnergyCalc();
	void Calculate(Stream* thestream);
private:
	void _calcFluid(Fluid* thefluid);

};

