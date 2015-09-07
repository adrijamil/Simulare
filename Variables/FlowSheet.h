#pragma once
#include "FSObject.h"
class FlowSheet :
	public FSObject
{
public:
	FlowSheet(){ _nchildren = 0; };
	~FlowSheet();
	bool Solve();

	void Add(FSObject* thechild);
	void Remove(){};//to be implemented


private:
	//int* _interface; //link this to some kinda interface object 
	FSObject** _children; //array of pointers to objects
	int _nchildren;
};

