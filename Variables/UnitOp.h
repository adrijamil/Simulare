#pragma once
#include "FSObject.h"

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
	virtual bool CanSolve()=0;

protected:
	Stream* _inletstreams=0;
	Stream* _outletstreams=0;
};

