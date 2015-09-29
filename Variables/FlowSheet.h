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

#ifndef __FLOWSHEET_H_INCLUDED__
#define __FLOWSHEET_H_INCLUDED__

#include "Stream.h"
#include "Valve.h"
#include "SolveStack.h"
#include "FSObject.h"
enum UnitOpEnum {VALVE,NINI};




class FlowSheet :
	public FSObject
{
public:
	FlowSheet()
	{
		_nchildren = 0;
		_stack = new SolveStack;

	};
	~FlowSheet();

	bool Solve();

	void Add(FSObject* thechild);
	void Remove(){};//to be implemented
	int NComps(){ return _default_package->NComps(); };
	void AddStream(string strname)
	{
		Stream* strm = new Stream(strname);
		if (!_default_package == 0)
		{
			strm->SetPropertyPackage(_default_package);
			Add(strm);
		}
		else
		{
			cout << "set package first";
		}
	}
	Stream* GetStream(string daname)
	{
		Stream* strmptr;
		strmptr = 0;
		for (int i = 0; i < _nchildren; i++)
		{
			if (_children[i]->Name() == daname)
			{
				strmptr = dynamic_cast<Stream *>(_children[i]);  //downcasting 
			}
		}

		return strmptr;
	}
	UnitOp* GetUnitOp(string daname)
	{
		UnitOp* UnitOpPtr;
		UnitOpPtr = 0;
		for (int i = 0; i < _nchildren; i++)
		{
			if (_children[i]->Name() == daname)
			{
				UnitOpPtr = dynamic_cast<UnitOp *>(_children[i]);  //downcasting 
			}
		}

		return UnitOpPtr;
	}
	void AddUnitOp(UnitOpEnum theUO,string thename)
	{
		switch (theUO)
		{
		case UnitOpEnum::VALVE:
			Valve* valve = new Valve(thename);
			Add(valve);
			break;
		}
	}

	void Output()
	{	
		Stream* strmptr;
		strmptr = 0;
		for (int i = 0; i < _nchildren; i++)
		{
			{
				strmptr = dynamic_cast<Stream *>(_children[i]);  //downcasting to stream type. later if unit ops how?
				strmptr->Output();
			}
		}
	}
protected:
	FSObject** _children; //array of pointers to objects  
	int _nchildren;
	string _name;
	PropPack* _default_package;
	SolveStack* _stack; //decouple this guy from stack
};

#endif
