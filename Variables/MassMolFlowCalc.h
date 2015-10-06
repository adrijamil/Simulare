#pragma once
#include "PropertyCalc.h"
#include "Stream.h"
#include "PropPack.h"


class MassMolFlowCalc :
	public PropertyCalc
{
public:
	MassMolFlowCalc();
	~MassMolFlowCalc();
	void Calculate();
};

