#include "stdafx.h"
#include "Compressor.h"
#include "ComponentBalance.h"
#include "HeatBalance.h"
#include "IsentropicCompression.h"

Compressor::Compressor()
{
	_bridgefunction = new BridgeFunction;
	_bridgefunction->SetParent(this);
	ComponentBalance* BF1 = new ComponentBalance;
	_bridgefunction->AddBridge(BF1);
	HeatBalance* BF2 = new HeatBalance;
	_bridgefunction->AddBridge(BF2);
	IsentropicCompression* BF3 = new IsentropicCompression;
	BF3->SetDeltaPressure(_deltapressure); //map unit op member variable to bridge function member variable
	BF3->SetEnergyInput(_energyinput);
	BF3->SetIsentropicEfficiency(_isentropicefficiency);
	_bridgefunction->AddBridge(BF3);
}


Compressor::~Compressor()
{
}

void Compressor::SpecifyVariable(RealVariableType vartype, double value)
{

		switch (vartype)
		{
		case DELTAPRESSURE:
			_deltapressure->SetValue(value);
			break;
		case ENERGYINPUT:
			_energyinput->SetValue(value);
			break;
		case ISENTROPICEFFICIENCY:
			_isentropicefficiency->SetValue(value);
			break;
		}
		
}


void Compressor::Output()
{
	cout << "\n";
	cout << _name << "\n";
	cout << "Delta Pressure  [kPa] " << _deltapressure->GetValue() << "\n";
	cout << "Energy Input[W] " << _energyinput->GetValue() << "\n";
	cout << "Isentropic Efficiency [frac]" << _isentropicefficiency->GetValue() << "\n";
}