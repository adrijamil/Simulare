#include "stdafx.h"
#include "UnitOp.h"
#include "Stream.h"

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
		_ninlets++;
		_inletstreams = (Stream**)realloc(_inletstreams, _ninlets* sizeof(*thestream));
		if (_inletstreams != NULL) //if it's null then realloc tak jadi
		{
			_inletstreams[_ninlets - 1] = &(*thestream);
		}
	}
	else if (InOrOut == 1)    
	{
		_noutlets++;

		_outletstreams = (Stream**)realloc(_outletstreams, _noutlets* sizeof(*thestream));
		if (_outletstreams != NULL) //if it's null then realloc tak jadi
		{
			_outletstreams[_noutlets - 1] = &(*thestream);
		}
	}

	

	//_items = new FSObject[_count];

	//realloc is similar to redim preserve. members of array are preserved and sent to new array (newchildren)
	//should be possible to reallocate straight to itself ie _children = (FSObject**)realloc(...... but this is safer. can catch errors.
	//is this safe? sizeof items may be different cos some are streams some are unit ops. 


	

}