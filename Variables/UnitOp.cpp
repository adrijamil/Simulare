#include "stdafx.h"
#include "UnitOp.h"


UnitOp::UnitOp()
{
}


UnitOp::~UnitOp()
{
}


void UnitOp::Connect(Stream* thestream, ConnectionType InOrOut)
{
	//do single stream in and out first
	if (InOrOut == 0)
	{
		_inletstreams = thestream;  
	}
	else if (InOrOut == 1)    
	{
		_outletstreams = thestream;
	}
}