#include "stdafx.h"
#include "BridgeFunction.h"
#include "Stream.h"

BridgeFunction::BridgeFunction()
{
}

BridgeFunction::~BridgeFunction()
{
}
bool BridgeFunction::Solve()
{
	BridgeFunction* thefunc;
	bool retval = true;
	bool thissolved = false;
	if (_nchildren == 0)
	{
		std::cout << "fuckme I'm A \n";
	}
	else// if got children solve all of them
	{
		for (int i = 0; i < _nchildren; i++)
		{
			thefunc = _children[i];

			thissolved = thefunc->Solve();
			if (thissolved == false){ retval = false; }
		}
	}

	return retval;

}

void BridgeFunction::SetParent(UnitOp* theOp)
{
	_parent = theOp;
}


void BridgeFunction::AddBridge(BridgeFunction* thechild)
{
	_nchildren = _nchildren + 1; //update count
	BridgeFunction** newchildren;
	cout << "\n";


	thechild->SetParent(_parent);
	//realloc is similar to redim preserve. members of array are preserved and sent to new array (newchildren)
	//should be possible to reallocate straight to itself ie _children = (FSObject**)realloc(...... but this is safer. can catch errors.
	newchildren = (BridgeFunction**)realloc(_children, _nchildren* sizeof(*thechild)); //allocate new array

	if (newchildren != NULL) //if it's null then realloc tak jadi
	{
		_children = newchildren;
		_children[_nchildren - 1] = &(*thechild);
	}
	//realloc is similar to redim preserve. members of array are preserved and sent to new array (newchildren)
	//should be possible to reallocate straight to itself ie _children = (FSObject**)realloc(...... but this is safer. can catch errors.

}