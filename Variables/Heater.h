#pragma once
#include "UnitOp.h"
#include "Stream.h"
class Heater :
	public UnitOp
{
public:
	bool Solve();
	RealVariable* K_Resistance(){ return _k_resistance; }
	RealVariable* PressureDrop(){ return _pressuredrop; }

	bool IsSolved(){ return _issolved; }
	Heater();
	Heater(string name);
	void Output();// later show something like pressure drop
	~Heater();
private:
	RealVariable* _k_resistance = new RealVariable;
	RealVariable* _pressuredrop = new RealVariable;
	RealVariable* _heatinput = new RealVariable;
	bool _issolved;

};

