#pragma once
//#include "UnitOp.h"
#include "Valve.h"



class UnitOpBuilder
{
public:
	enum UnitOpEnum { VALVE, NINI };

	UnitOpBuilder()
	{
		_currentunitop = 0;
	};
	virtual void BuildUnitOp(UnitOpEnum theop)
	{
		switch (theop)
		{
		case UnitOpEnum::VALVE:
			_currentunitop = new Valve;
			break;
		default:
			break;
		}
	}
	void Connect(Stream* thestream, ConnectionType contype){ _currentunitop->Connect(thestream, contype); };
	virtual void EditUnitOp(UnitOp* existingop){ _currentunitop = existingop; }
	virtual UnitOp* GetUnitOp(){ return _currentunitop; };
	~UnitOpBuilder();
private:
	UnitOp* _currentunitop;
	
};

