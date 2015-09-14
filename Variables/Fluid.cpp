#include "stdafx.h"
#include "Fluid.h"


Fluid::Fluid()
{
}


Fluid::~Fluid()
{
}


void Fluid::Normalise()
{
	double* thecomps;
	double thesum=0;
		thecomps = _composition->GetValues();
		//cout << _composition->Size();
		int Nelements = _composition->Size();
		for (int i = 0; i < Nelements; i++)
	{
		thesum = thesum +_composition->GetValue(i);
	}

		for (int i = 0; i < Nelements; i++)
	{
		_composition->SetValue(i, _composition->GetValue(i) / thesum);
	}

}

