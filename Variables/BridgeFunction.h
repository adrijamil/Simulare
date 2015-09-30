#pragma once
// to be used by unit ops
//could make this a composite
#include "UnitOp.h"

class BridgeFunction
{
public:
	BridgeFunction();
	~BridgeFunction();
	virtual bool Solve()=0;
private:
	UnitOp* _parent;
};

