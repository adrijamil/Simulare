#pragma once
#include "PropertyCalc.h"
#include "Stream.h"
class RPMassDensityCalc :
	public PropertyCalc
{
public:
	RPMassDensityCalc();
	~RPMassDensityCalc();
	bool Calculate();
	RealVariable** GetVariables(Stream* refstream);
};

