#pragma once
#include "PropertyCalc.h"
#include "Stream.h"

class DensityCalc :
	public PropertyCalc
{
public:
	DensityCalc();
	~DensityCalc();
	void Calculate(Stream* thestream);

private:
	void CalcFluid(Fluid* thefluid);
};