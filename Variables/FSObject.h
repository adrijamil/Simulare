// ===============================
// AUTHOR     :		Adri
// CREATED(d/m/yy):	7/9/15
// PURPOSE     :	This is generic interface abstract base class for flowsheet objects (flowsheet, stream, unitop)
//					Any common functions/data should be here
//					
// SPECIAL NOTES:	
// ===============================
// Change History: - put name, date and description of change
// 1. Created
//==================================



#ifndef __FSOBJECT_H_INCLUDED__
#define __FSOBJECT_H_INCLUDED__
#include "StackObject.h"
using namespace std;
class FSObject
{
public:
	FSObject() {

		_name = " ";
	}
	~FSObject();
	virtual bool Solve() = 0;// { return false; };
	string Name() { return _name; }
	void SetName(string thename) { _name = thename; }
	virtual StackObject* GetStackObject(int i){ return _stackobjects[i]; }

	virtual int NStackObjects(){ return _nstackobjects; }

protected:
	string _name;
	StackObject** _stackobjects;
	int _nstackobjects = 0;


};

#endif
