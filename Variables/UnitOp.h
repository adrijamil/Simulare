#pragma once
#include "FSObject.h"
#include "BridgeFunction.h"
enum ConnectionType
{
	INLET, OUTLET
};

class Stream;


class UnitOp :
	public FSObject
{
public:
	UnitOp();
	~UnitOp();
	virtual void Connect(Stream* thestream, ConnectionType InOrOut);
	virtual bool Solve()=0;
	int NOutlets(){ return _noutlets; }
	int NInlets(){ return _ninlets; }
	Stream* GetStream(int i, ConnectionType ConType);


protected:
	Stream** _inletstreams=0;
	Stream** _outletstreams=0;
	int _ninlets=0;
	int _noutlets=0;
	BridgeFunction* _bridgefunction; //only one will be added, which will be a composite of functions;
};

