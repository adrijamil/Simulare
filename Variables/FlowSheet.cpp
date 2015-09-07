#include "stdafx.h"
#include "FlowSheet.h"





FlowSheet::~FlowSheet()
{
}


void FlowSheet::Add(FSObject* theobject)
{
	 _nchildren = _nchildren + 1;
	 FSObject** newchildren;
	 cout << "\n";
	// _children = new FSObject*[_nchildren];

	 // this is not a good way to allocate memory for composite objects I think.
	 //cout << sizeof(theobject);
	 newchildren = (FSObject**)realloc(_children, _nchildren* sizeof(*theobject));

	 if (newchildren != NULL) 
	 {
		 _children = newchildren;
		_children[_nchildren-1] = &(*theobject);
	 }


}


bool FlowSheet::Solve()
{

	if (_nchildren == 0)
	{
		std::cout << "fuckme I'm A \n";
	}
	else
	{
		for (int i = 0; i < _nchildren; i++)
		{
			_children[i]->Solve();
		}
	}
	return true;

}