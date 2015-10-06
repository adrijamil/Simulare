
#include "stdafx.h"
#include "Mixer.h"
#include "ComponentBalance.h"
#include "HeatBalance.h"
#include "PressureBalance.h"

Mixer::Mixer()
{
	_bridgefunction = new BridgeFunction;
	_bridgefunction->SetParent(this);
	ComponentBalance* BF1 = new ComponentBalance;
	_bridgefunction->AddBridge(BF1);
	HeatBalance* BF2 = new HeatBalance;
	_bridgefunction->AddBridge(BF2);
	PressureBalance* BF3 = new PressureBalance;
	_bridgefunction->AddBridge(BF3);
}


Mixer::Mixer(string name)
{
	_name = name;

	_bridgefunction = new BridgeFunction;
	_bridgefunction->SetParent(this);
	ComponentBalance* BF1 = new ComponentBalance;
	_bridgefunction->AddBridge(BF1);
	HeatBalance* BF2 = new HeatBalance;
	_bridgefunction->AddBridge(BF2);
	PressureBalance* BF3 = new PressureBalance;
	_bridgefunction->AddBridge(BF3);
}

Mixer::~Mixer()
{
}