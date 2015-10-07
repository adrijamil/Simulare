#pragma once
//#include "UnitOp.h"
#include "Valve.h"
#include "Heater.h"
#include "Mixer.h"
#include "Splitter.h"

enum UnitOpEnum { VALVE, HEATER, MIXER, SPLITTER };
class UnitOpBuilder
{
public:


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
		case UnitOpEnum::HEATER:
			_currentunitop = new Heater;
			break;
		case UnitOpEnum::MIXER:
			_currentunitop = new Mixer;
			break;
		case UnitOpEnum::SPLITTER:
			_currentunitop = new Splitter;
			break;
		default:
			break;
		}
	}
	void SetName(string thename)
	{
		_currentunitop->SetName(thename);
	}
	void Connect(Stream* thestream, ConnectionType contype){ _currentunitop->Connect(thestream, contype); };
	void SpecifyVariable(RealVariableType vartype, double value)
	{
		_currentunitop->SpecifyVariable(vartype, value);
	}
	virtual void EditUnitOp(UnitOp* existingop){ _currentunitop = existingop; }
	virtual UnitOp* GetUnitOp(){ return _currentunitop; };
	~UnitOpBuilder();
private:
	UnitOp* _currentunitop;
	
};

