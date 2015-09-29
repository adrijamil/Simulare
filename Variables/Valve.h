#pragma once
#include "UnitOp.h"
#include "Stream.h"
class Valve :
	public UnitOp
{
public:
	bool Solve();
	RealVariable* K_Resistance(){ return _k_resistance; }
	RealVariable* PressureDrop(){ return _pressuredrop; }
	bool CanSolve();
	bool IsSolved(){ return _issolved; }
	Valve();
	~Valve();
private:
	RealVariable* _k_resistance = new RealVariable;
	RealVariable* _pressuredrop = new RealVariable;
	bool _issolved;
	enum CalcModeEnum { FKP1,FKP2,FP1P2,KP1P2};//what is specified?
	CalcModeEnum CalcMode;
};

