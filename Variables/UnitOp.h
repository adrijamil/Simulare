#pragma once
#include "FSObject.h"
#include "BridgeFunction.h"

enum ConnectionType
{
	INLET, OUTLET
};

class Stream;

class BridgeFunction;

class UnitOp :
	public FSObject
{
public:
	UnitOp();
	~UnitOp();
	virtual void Connect(Stream* thestream, ConnectionType InOrOut);
	bool Solve();
	int NOutlets(){ return _noutlets; }
	int NInlets(){ return _ninlets; }
	Stream* GetStream(int i, ConnectionType ConType);
	virtual void SpecifyVariable(RealVariableType vartype, double value){};//maybe make this template so can specify on off. or just leave as double and use 1 and 0;
	bool IsSolved(){ return _issolved; }
protected:
	Stream** _inletstreams=0;
	Stream** _outletstreams=0;
	int _ninlets=0;
	int _noutlets=0;
	BridgeFunction* _bridgefunction; //only one will be added, which will be a composite of functions;
	bool _issolved;
};

