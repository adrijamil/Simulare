#pragma once
#include "BridgeFunction.h"
class SimpleResistanceEquation :
	public BridgeFunction
{
public:
	bool Solve();
	SimpleResistanceEquation();
	~SimpleResistanceEquation();
	void SetResistance(RealVariable* thevar)
	{
		_k_resistance = thevar;
	}
	void SetPressureDrop(RealVariable* thevar)
	{
		_pressuredrop = thevar;
	}
private:
	RealVariable* _k_resistance=0;
	RealVariable* _pressuredrop = 0;


};

