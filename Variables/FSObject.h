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
using namespace std;
class FSObject
{
public:
	FSObject() {

		_name = " ";
	}

	~FSObject();
	virtual bool Solve()=0;
	
	string Name() { return _name; }
	//void Add(FSObject* thechild);
	//void Remove(){};


protected:
	string _name;;
	//int* _interface; //link this to some kinda interface object 
	//FSObject** _children; //array of pointers to objects
	//int _nchildren;
};

#endif
