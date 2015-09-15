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

	//calc specs
	int nspecs=0;

	if (!_pressure->IsCalculated())
	{
		nspecs = nspecs + 1;
	}

	if (!_temperature->IsCalculated())
	{
		nspecs = nspecs + 1;
	}

	if (!_phases[0]->PhaseMoleFraction()->IsCalculated())
	{
		nspecs = nspecs + 1;
	}

	if (!_molenthalpy->IsCalculated())
	{
		nspecs = nspecs + 1;
	}

	if (!_molentropy->IsCalculated())
	{
		nspecs = nspecs + 1;
	}

	if (!_composition->IsCalculated())
	{
		nspecs = nspecs + 1;
	}

	if ((nspecs > 3))
	{
		cout << "Specifation error";
		return false;
	}

	if ((!(_pressure->IsCalculated())) && (!(_temperature->IsCalculated())))
	{
		if ((_pressure->IsKnown()) && (_temperature->IsKnown()))
		{
			PTFlashMe();
		}
	}
	else if ((!(_phases[0]->PhaseMoleFraction()->IsCalculated())) && (!(_temperature->IsCalculated())))
	{
		if ((_phases[0]->PhaseMoleFraction()->IsKnown()) && (_temperature->IsKnown()))
		{
			TQFlashMe();
		}
	}
	

	_proppack->Properties()->Calculate(this);

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
	cout << "Mw  " << MolecularWeight()->GetValue() << "\n";
	cout << "Vfrac  " << VapourFraction()->GetValue() << "\n";
	cout << "GasPhase  " << "\n";
	cout << "Mw  " << _phases[0]->MolecularWeight()->GetValue() << "\n";
	for (int k = 0; k < myncomps; k++)
	{

		cout << _proppack->GetComponent(k).Name << "  " << _phases[0]->Composition()->GetValue(k) << "\n";
	}

	cout << "\n";
	cout << "LiquidPhase" << "\n";
	cout << "Mw  " << _phases[1]->MolecularWeight()->GetValue() << "\n";
	for (int k = 0; k < myncomps; k++)
	{
		cout << _proppack->GetComponent(k).Name << "  " << _phases[1]->Composition()->GetValue(k) << "\n";
	}
}