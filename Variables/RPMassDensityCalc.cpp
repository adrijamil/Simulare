#include "stdafx.h"
#include "RPMassDensityCalc.h"


RPMassDensityCalc::RPMassDensityCalc()
{
}


RPMassDensityCalc::~RPMassDensityCalc()
{
}
void RPMassDensityCalc::Calculate(Stream* thestream)
{
	double gasmassd;
	double totmassd;
	double liqmassd;

	gasmassd = (thestream->Phases(0)->MolarDensity()->GetValue())*(thestream->Phases(0)->MolecularWeight()->GetValue()) / 1000;
	thestream->Phases(0)->MassDensity()->SetValue(gasmassd);
	liqmassd = (thestream->Phases(1)->MolarDensity()->GetValue())*(thestream->Phases(1)->MolecularWeight()->GetValue()) / 1000;
	thestream->Phases(1)->MassDensity()->SetValue(liqmassd);
	totmassd = (thestream->MolarDensity()->GetValue())*(thestream->MolecularWeight()->GetValue()) / 1000;
	thestream->MassDensity()->SetValue(totmassd);

}