#include "stdafx.h"
#include "FlowSheet.h"
#include "SolveStack.h"




FlowSheet::~FlowSheet()
{
}


void FlowSheet::Add(FSObject* theobject)
{
	
	 _nchildren = _nchildren + 1; //update count
	 FSObject** newchildren; 
	 cout << "\n";

	 //realloc is similar to redim preserve. members of array are preserved and sent to new array (newchildren)
	 //should be possible to reallocate straight to itself ie _children = (FSObject**)realloc(...... but this is safer. can catch errors.
	 newchildren = (FSObject**)realloc(_children, _nchildren* sizeof(*theobject)); //allocate new array

	 if (newchildren != NULL) //if it's null then realloc tak jadi
	 {
		 _children = newchildren; 
		_children[_nchildren-1] = &(*theobject);
	 }
	 
	 _stack->Add(theobject);

}




bool FlowSheet::Solve()
{
	bool retval;

	retval=_stack->Solve();
	return retval;
}