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
	 

}




bool FlowSheet::Solve()
{
	bool retval;

	for (int i = 0; i < _nchildren; i++)
	{
		for (int j = 0; j < _children[i]->NStackObjects(); j++)
		{
			if (_children[i]->GetStackObject(j)->IsDirty())
			{
				_stack->Add(_children[i]->GetStackObject(j));
			}
		}
	}

	//Stack->Forget();
	
	retval=_stack->Solve();
	return retval;
}