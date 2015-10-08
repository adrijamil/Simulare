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
	if (_issolved == true)
	{
		return true;
	}
	
	bool retval=true;
	//check DOF then call appropriate flash

	//calc specs
	FlashTypeEnum thetype;

	int nspecs=0;

	if (_pressure->IsKnown())
	{
		nspecs = nspecs + 1;
	}

	if (_temperature->IsKnown())
	{
		nspecs = nspecs + 1;
	}

	if (_phases[0]->PhaseMoleFraction()->IsKnown())
	{
		nspecs = nspecs + 1;
	}

	if (_molenthalpy->IsKnown())
	{
		nspecs = nspecs + 1;
	}

	if (_molentropy->IsKnown())
	{
		nspecs = nspecs + 1;
	}

	if (_composition->IsKnown())
	{
		nspecs = nspecs + 1;
	}

	if ((nspecs < 3))
	{
		cout << "Specifation error \n";
		retval = false;
		_proppack->RefStream()->ReadStream(this);
		goto othercalcs;
	}

	//if ((!(_pressure->IsCalculated())) && (!(_temperature->IsCalculated())))
	//{
		if ((_pressure->IsKnown()) && (_temperature->IsKnown()))
		{
			//PTFlashMe();
			thetype = PT;

		}
	//}
	//else if ((!(_phases[0]->PhaseMoleFraction()->IsCalculated())) && (!(_temperature->IsCalculated())))
	//{
		else if ((_phases[0]->PhaseMoleFraction()->IsKnown()) && (_temperature->IsKnown()))
		{
			//TQFlashMe();
			thetype = TQ;
		}
	//}
	//else if ((!(_phases[0]->PhaseMoleFraction()->IsCalculated())) && (!(_pressure->IsCalculated())))
	//{
		else if ((_phases[0]->PhaseMoleFraction()->IsKnown()) && (_pressure->IsKnown()))
		{
			//PQFlashMe();
			thetype = PQ;
		}
	//}
	//else if ((!(_molenthalpy->IsCalculated())) && (!(_pressure->IsCalculated())))
	//{
		else if ((_molenthalpy->IsKnown()) && (_pressure->IsKnown()))
		{
			//PQFlashMe();
			thetype = PH;
		}
	//}
	//else if ((!(_molentropy->IsCalculated())) && (!(_pressure->IsCalculated())))
	//{
		else if ((_molentropy->IsKnown()) && (_pressure->IsKnown()))
		{
			//PQFlashMe();
			thetype = PS;
		}
	//}
	//else if ((!(_molentropy->IsCalculated())) && (!(_temperature->IsCalculated())))
	//{
		else if ((_molentropy->IsKnown()) && (_temperature->IsKnown()))
		{
			//PQFlashMe();
			thetype = TS;
		}
	//}
	//else if ((!(_molenthalpy->IsCalculated())) && (!(_temperature->IsCalculated())))
	//{
		else if ((_molenthalpy->IsKnown()) && (_temperature->IsKnown()))
		{
			//PQFlashMe();
			thetype = TH;
		}
	//}
	
	//Flash(thetype)

		_proppack->RefStream()->ReadStream(this);
		if (!_proppack->Flash(thetype))
		{
			retval = false;
		}

	othercalcs:
	if (!_proppack->Properties()->Calculate())
	{
		retval = false;
	}
	_proppack->RefStream()->WriteStream(this);
	
	_issolved = retval;
	return _issolved;

}


void Stream::Output()
{
	int myncomps;
	myncomps = _proppack->NComps();

	cout << "\n";
	cout << _name<< "\n";

	cout << "Pressure  [kPa] " << Pressure()->GetValue()<< "\n";
	cout << "Temperature  [K] " << Temperature()->GetValue() << "\n";
	cout << "MassFlow  [kg/h] " << MassFlow()->GetValue() << "\n";
	cout << "MolarFlow  [kmol/h] " << MolarFlow()->GetValue() << "\n";
	cout << "Mw  [g/mol] " << MolecularWeight()->GetValue() << "\n";
	//RealVariable* rv = MassDensity();
	cout << "MassDensity  [kg/m3] " << MassDensity()->GetValue() << "\n";
	cout << "MolarDensity  [mol/m3] " << MolarDensity()->GetValue() << "\n";
	cout << "MolarEnthalpy  [J/mol] " << MolarEnthalpy()->GetValue() << "\n";
	cout << "MolarEntropy  [J/mol/K] " << MolarEntropy()->GetValue() << "\n";
	cout << "Vfrac  " << VapourFraction()->GetValue() << "\n\n";
	for (int k = 0; k < myncomps; k++)
	{

		cout << _proppack->GetComponent(k).Name << "  " << Composition()->GetValue(k) << "\n";
	}

	cout << "\n" << "GasPhase  " << "\n";
	cout << "Fraction  [mol/mol] " << _phases[0]->PhaseMoleFraction()->GetValue() << "\n";
	cout << "MassFlow  [kg/h] " << _phases[0] -> MassFlow()->GetValue() << "\n";
	cout << "MolarFlow  [kmol/h] " << _phases[0] -> MolarFlow()->GetValue() << "\n";
	cout << "Mw  [g/mol] " << _phases[0]->MolecularWeight()->GetValue() << "\n";
	cout << "MassDensity  [kg/m3] " << _phases[0]->MassDensity()->GetValue() << "\n";
	cout << "MolarDensity  [mol/m3] " << _phases[0]->MolarDensity()->GetValue() << "\n";
	cout << "MolarEnthalpy  [J/mol] " << _phases[0]->MolarEnthalpy()->GetValue() << "\n";
	cout << "MolarEntropy  [J/mol/K] " << _phases[0]->MolarEntropy()->GetValue() << "\n";
	for (int k = 0; k < myncomps; k++)
	{

		cout << _proppack->GetComponent(k).Name << "  " << _phases[0]->Composition()->GetValue(k) << "\n";
	}

	cout << "\n";
	cout << "LiquidPhase" << "\n";
	cout << "Fraction  [mol/mol] " << _phases[1]->PhaseMoleFraction()->GetValue() << "\n";
	cout << "MassFlow  [kg/h] " << _phases[1] -> MassFlow()->GetValue() << "\n";
	cout << "MolarFlow  [kmol/h] " << _phases[1] ->MolarFlow()->GetValue() << "\n";
	cout << "Mw  " << _phases[1]->MolecularWeight()->GetValue() << "\n";
	cout << "MassDensity  [kg/m3] " << _phases[1]->MassDensity()->GetValue() << "\n";
	cout << "MolarDensity  [mol/m3] " << _phases[1]->MolarDensity()->GetValue() << "\n";
	cout << "MolarEnthalpy  [J/mol] " << _phases[1]->MolarEnthalpy()->GetValue() << "\n";
	cout << "MolarEntropy  [J/mol/K] " << _phases[1]->MolarEntropy()->GetValue() << "\n";
	for (int k = 0; k < myncomps; k++)
	{
		cout << _proppack->GetComponent(k).Name << "  " << _phases[1]->Composition()->GetValue(k) << "\n";
	}
}