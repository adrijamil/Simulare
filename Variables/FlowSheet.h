// ===============================
// AUTHOR     :		Adri
// CREATED(d/m/yy): 7/9/15
// PURPOSE     :	This is a subclass of the FSObject. 
//					This object will contain Stream, UnitOp and FlowSheet
//					uses the composite pattern to recursively solve itself
// SPECIAL NOTES:	The idea is to treat Stream, UnitOp and FlowSheet in a similar fashion
// ===============================
// Change History: - put name, date and description of change
// 1. Created
//==================================

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
	FSObject** _children; //array of pointers to objects  
	int _nchildren;
};

