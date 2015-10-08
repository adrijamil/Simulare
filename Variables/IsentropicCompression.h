#pragma once
#include "BridgeFunction.h"
class IsentropicCompression :
	public BridgeFunction
{
public:
	bool Solve();
	IsentropicCompression();
	~IsentropicCompression();
	
	void SetDeltaPressure(RealVariable* thevar)
	{
		_deltapressure = thevar;
	}
	void SetEnergyInput(RealVariable* thevar)
	{
		_energyinput = thevar;
	}
	void SetIsentropicEfficiency(RealVariable* thevar)
	{
		_isentropicefficiency = thevar;
	}
private:
	RealVariable* _energyinput = 0;//set to zero because it needs to be mapped to a variable member of a unit op. cannot exist on its own.
	RealVariable* _isentropicefficiency = 0;
	RealVariable* _deltapressure = 0;


};
