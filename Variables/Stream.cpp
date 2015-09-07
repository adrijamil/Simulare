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

	cout << "\n" << "\n";
	cout << _phases[0]->Composition()->GetValue(0)<<"\n";
	cout << _phases[0]->Composition()->GetValue(1) << "\n";
	cout << _phases[0]->Composition()->GetValue(2) << "\n";
	return true;
}