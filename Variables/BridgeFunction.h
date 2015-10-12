#pragma once
// to be used by unit ops
//could make this a composite

#include "RealVariable.h".
#include "StackObject.h"

class UnitOp;

class BridgeFunction:
	public StackObject
{
public:
	BridgeFunction();
	~BridgeFunction();
	virtual bool Solve();
	void SetParent(UnitOp* theOp);
	void AddBridge(BridgeFunction* thechild);
	bool IsSolved(){ return _solved; }
	int NStackObjects(){ return _nchildren; }
	StackObject* GetStackObject(int i)
	{
		return _children[i];
	}
protected:
	UnitOp* _parent;
	BridgeFunction** _children;
	int _nchildren;
	bool _solved;
};

