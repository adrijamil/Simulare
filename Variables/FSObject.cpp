#include "stdafx.h"
#include "FSObject.h"





FSObject::~FSObject()
{
}
//
//
//void FSObject::Add(FSObject* theobject)
//{
//	 _nchildren = _nchildren + 1;
//	 FSObject** newchildren;
//	 cout << "\n";
//	// _children = new FSObject*[_nchildren];
//
//	 // this is not a good way to allocate memory for composite objects I think.
//	 //cout << sizeof(theobject);
//	 newchildren = (FSObject**)realloc(_children, _nchildren* sizeof(&theobject));
//
//	 if (newchildren != NULL) {
//		 _children = newchildren;
//		 if (!(_nchildren == 1))
//		 {
//			_children[_nchildren-1] = &*theobject;
//		 }
//		 
//	 }
//
//
//}
//
//
//
//
//
//bool FSObject::Solve()
//{
//	FSObject* theobj;
//
//	bool thebool;
//	if (!(_nchildren == 0))
//	{
//		for (int i = 0; i < _nchildren; i++)
//		{
//			theobj = _children[i];
//
//			thebool = theobj->Solve();
//		}
//	}
//	else
//	{
//		Solve();
//	}
//	
//	return thebool;
//}
