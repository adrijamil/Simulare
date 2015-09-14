#include "stdafx.h"
#include "Stream.h"


Stream::Stream()
{
	_phases[0] = new Phase(VAPOUR);
	_phases[1] = new Phase(HCLIQUID);
	_phases[2] = new Phase(AQUEOUS);

	_pressure = new RealVariable;
	_temperature = new RealVariable;

	_phases[0]->SetParent(this);
	_phases[1]->SetParent(this);
	_phases[2]->SetParent(this);
	//_phases[0]->_pressure = _pressure;

	_name = "fuck";
}
Stream::Stream(string daname)
{
	_phases[0] = new Phase(VAPOUR);
	_phases[1] = new Phase(HCLIQUID);
	_phases[2] = new Phase(AQUEOUS);

	_pressure = new RealVariable;
	_temperature = new RealVariable;

	_phases[0]->SetParent(this);
	_phases[1]->SetParent(this);
	_phases[2]->SetParent(this);
	//_phases[0]->_pressure = _pressure;

	_name = daname;
}

void Stream::SetPropertyPackage(PropPack* thePP)
{
	_proppack = thePP;
}


Stream::~Stream()
{
}


bool Stream::Solve()
{
	//check DOF then call appropriate flash
	PTFlashMe();
	return true;
}




void Stream::Output()
{
	int myncomps;
	myncomps = _proppack->NComps();

	cout << "\n";
	cout << _name<< "\n";

	cout << "Pressure  " << Pressure()->GetValue()<< "\n";
	cout << "Temperature  " << Temperature()->GetValue() << "\n";
	cout << "Vfrac  " << VapourFraction()->GetValue() << "\n";
	cout << "GasPhase  " << "\n";
	for (int k = 0; k < myncomps; k++)
	{

		cout << _proppack->GetComponent(k).Name << "  " << _phases[0]->Composition()->GetValue(k) << "\n";
	}

	cout << "\n";
	cout << "LiquidPhase" << "\n";
	for (int k = 0; k < myncomps; k++)
	{
		cout << _proppack->GetComponent(k).Name << "  " << _phases[1]->Composition()->GetValue(k) << "\n";
	}



}