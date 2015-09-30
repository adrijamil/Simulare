#pragma once
// to be used by unit ops
//could make this a composite

#include "RealVariable.h"
class UnitOp;

class BridgeFunction
{
public:
	BridgeFunction();
	~BridgeFunction();
	virtual bool Solve();
	void SetParent(UnitOp* theOp);
	void AddBridge(BridgeFunction* thechild);

protected:
	UnitOp* _parent;
	BridgeFunction** _children;
	int _nchildren;
};

