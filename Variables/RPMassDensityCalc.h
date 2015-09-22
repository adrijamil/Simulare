#pragma once
#include "PropertyCalc.h"
#include "Stream.h"
class RPMassDensityCalc :
	public PropertyCalc
{
public:
	RPMassDensityCalc();
	~RPMassDensityCalc();
	void Calculate(Stream* thestream);
};

