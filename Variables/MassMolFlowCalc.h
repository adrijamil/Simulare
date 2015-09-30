#pragma once
#include "PropertyCalc.h"
#include "Stream.h"


class MassMolFlowCalc :
	public PropertyCalc
{
public:
	MassMolFlowCalc();
	~MassMolFlowCalc();
	void Calculate(Stream* thestream);
private:
private:
	void CalcFluid(Fluid* thefluid);
};

