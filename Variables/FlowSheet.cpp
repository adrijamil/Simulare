#include "stdafx.h"
#include "FlowSheet.h"





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

//solving of children will return bools to say solved or not. implement a way to check if all have solved before returning a value.

	//if no children do this
	if (_nchildren == 0)
	{
		std::cout << "fuckme I'm A \n";
	}
	else// if got children solve all of them
	{
		for (int i = 0; i < _nchildren; i++)
		{
			_children[i]->Solve();
		}
	}
	return true;

}