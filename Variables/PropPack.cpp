#include "stdafx.h"
#include "PropPack.h"


PropPack<>::PropPack()
{
	_components[0].Name = "Methane";
	_components[0].Acentric = 0.01;
	_components[0].ID = 1;
	_components[0].Mw = 16.04;
	_components[0].Pc = 4599;
	_components[0].Tc = 190.85;

	_components[0].Name = "Ethane";
	_components[0].Acentric = 0.1;
	_components[0].ID = 2;
	_components[0].Mw = 30.07;
	_components[0].Pc = 4880;
	_components[0].Tc = 305;

	_components[0].Name = "Benzene";
	_components[0].Acentric = 0.212;
	_components[0].ID = 3;
	_components[0].Mw = 78.11;
	_components[0].Pc = 4898;
	_components[0].Tc = 562.12;

}

template<>
void PropPack<Stream>::PT_Flash(Stream* thestream)
{
	cout << "im flashing with " << _name;
};

PropPack<>::~PropPack()
{
}

