#include "stdafx.h"
#include "Heater.h"
#include "ComponentBalance.h"
#include "HeatBalance.h"
#include "SimpleResistanceEquation.h"

Heater::Heater()
{
	_bridgefunction = new BridgeFunction;
	_bridgefunction->SetParent(this);
	ComponentBalance* BF1 = new ComponentBalance;
	_bridgefunction->AddBridge(BF1);
	HeatBalance* BF2 = new HeatBalance;
	BF2->SetHeatInput(_heatinput);
	_bridgefunction->AddBridge(BF2);
	SimpleResistanceEquation* BF3 = new SimpleResistanceEquation;
	BF3->SetResistance(_k_resistance);
	BF3->SetPressureDrop(_pressuredrop);
	_bridgefunction->AddBridge(BF3);
}


Heater::Heater(string name)
{
	_name = name;
	_bridgefunction = new BridgeFunction;
	_bridgefunction->SetParent(this);
	ComponentBalance* BF1 = new ComponentBalance;
	_bridgefunction->AddBridge(BF1);
	HeatBalance* BF2 = new HeatBalance;
	BF2->SetHeatInput(_heatinput);
	_bridgefunction->AddBridge(BF2);
	SimpleResistanceEquation* BF3 = new SimpleResistanceEquation;
	BF3->SetResistance(_k_resistance);
	BF3->SetPressureDrop(_pressuredrop);
	_bridgefunction->AddBridge(BF3);
}

Heater::~Heater()
{
}




void Heater::Output()
{
	cout << "\n";
	cout << _name << "\n";
	cout << "K resistance  [kPa-kg/h] " << K_Resistance()->GetValue() << "\n";
	cout << "Pressure Drop  [kPa] " << PressureDrop()->GetValue() << "\n";
	cout << "Heat Input  [W] " << HeatInput()->GetValue() << "\n";
}

void Heater::SpecifyVariable(RealVariableType vartype, double value)
{
	switch (vartype)
	{
	case PRESSUREDROP:
		_pressuredrop->SetValue(value);
		break;
	case K_RESISTANCE:
		_k_resistance->SetValue(value);
		break;
	case HEATINPUT:
		_heatinput->SetValue(value);
		break;
	}
}