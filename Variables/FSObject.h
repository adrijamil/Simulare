#ifndef __FSOBJECT_H_INCLUDED__
#define __FSOBJECT_H_INCLUDED__
using namespace std;
class FSObject
{
public:
	FSObject() {

		_FSOname = " ";
	}

	~FSObject();
	virtual bool Solve()=0;
	

	//void Add(FSObject* thechild);
	//void Remove(){};


private:
	string _FSOname;
	//int* _interface; //link this to some kinda interface object 
	//FSObject** _children; //array of pointers to objects
	//int _nchildren;
};

#endif
