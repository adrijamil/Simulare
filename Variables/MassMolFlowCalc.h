#pragma once
#include "PropertyCalc.h"
#include "Stream.h"
#include "PropPack.h"


class MassMolFlowCalc :
	public PropertyCalc
{
public:
	//_refstream = theRS;
	MassMolFlowCalc();
	~MassMolFlowCalc();
	bool Calculate();
	RealVariable** GetVariables(Stream* refstream);
};

