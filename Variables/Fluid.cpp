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
		cout << _composition->Size();
		int Nelements = _composition->Size();
		for (int i = 0; i < Nelements; i++)
	{
		cout << thecomps[i];
		thesum = thesum + thecomps[i];
	}

		for (int i = 0; i < Nelements; i++)
	{
		thecomps[i] = thecomps[i]/thesum;
		cout << thecomps[i];
	}
	_composition->SetValue(*thecomps);
}

