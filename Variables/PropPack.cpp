#include "stdafx.h"
#include "PropPack.h"


PropPack::PropPack()
{

	//make components manually cos im a lazyfuck
	_components[0].Name = "METHANE";
	_components[0].Acentric = 0.01;
	_components[0].ID = 1;
	_components[0].Mw = 16.04;
	_components[0].Pc = 4599;
	_components[0].Tc = 190.85;

	_components[1].Name = "ETHANE";
	_components[1].Acentric = 0.1;
	_components[1].ID = 2;
	_components[1].Mw = 30.07;
	_components[1].Pc = 4880;
	_components[1].Tc = 305;

	_components[2].Name = "BENZENE";
	_components[2].Acentric = 0.212;
	_components[2].ID = 3;
	_components[2].Mw = 78.11;
	_components[2].Pc = 4898;
	_components[2].Tc = 562.12;
	_ncomps = 3;

}




PropPack::~PropPack()
{
}

