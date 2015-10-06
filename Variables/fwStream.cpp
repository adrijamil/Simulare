#include "stdafx.h"
#include "fwStream.h"
#include "Stream.h"

fwStream::fwStream()
{
}

void fwStream::ReadStream(Stream* thestream)
{
	if (this == NULL)
	{
		cout << "how am i nothing";
	}
	NComps =thestream->NComps();
	
	Liquid.Composition  =new double[NComps];
	Vapour.Composition = new double[NComps];
	Overall.Composition = new double[NComps];

	Pressure=thestream->Pressure()->GetValue();
	Temperature = thestream->Temperature()->GetValue();

	Overall.Enthalpy = thestream->MolarEnthalpy()->GetValue();
	Overall.Entropy = thestream->MolarEntropy()->GetValue();
	Overall.MolarDensity = thestream->MolarDensity()->GetValue();
	Overall.MolecularWeight = thestream->MolecularWeight()->GetValue();
	Overall.Composition = thestream->Composition()->GetValues();


	Liquid.Enthalpy = thestream->Phases(1)->MolarEnthalpy()->GetValue();
	Liquid.Entropy = thestream->Phases(1)->MolarEntropy()->GetValue();
	Liquid.MolarDensity = thestream->Phases(1)->MolarDensity()->GetValue();
	Liquid.MolecularWeight = thestream->Phases(1)->MolecularWeight()->GetValue();
	Liquid.Composition = thestream->Phases(1)->Composition()->GetValues();

	Vapour.Enthalpy = thestream->Phases(0)->MolarEnthalpy()->GetValue();
	Vapour.Entropy = thestream->Phases(0)->MolarEntropy()->GetValue();
	Vapour.MolarDensity = thestream->Phases(0)->MolarDensity()->GetValue();
	Vapour.MolecularWeight = thestream->Phases(0)->MolecularWeight()->GetValue();
	Vapour.Composition = thestream->Phases(0)->Composition()->GetValues();
	

}
fwStream::~fwStream()
{
	
}
void fwStream::WriteStream(Stream* thestream)
{
	
	thestream->Pressure()->SetValue(Pressure);
	thestream->Temperature()->SetValue(Temperature);

	thestream->MolarEnthalpy()->SetValue(Overall.Enthalpy);
	thestream->MolarEntropy()->SetValue(Overall.Entropy);
	thestream->MolarDensity()->SetValue(Overall.MolarDensity);
	thestream->MolecularWeight()->SetValue(Overall.MolecularWeight);
	thestream->Composition()->SetValues(NComps, Overall.Composition);

	thestream->Phases(1)->MolarEnthalpy()->SetValue(Liquid.Enthalpy);
	thestream->Phases(1)->MolarEntropy()->SetValue(Liquid.Entropy);
	thestream->Phases(1)->MolarDensity()->SetValue(Liquid.MolarDensity);
	thestream->Phases(1)->MolecularWeight()->SetValue(Liquid.MolecularWeight);
	thestream->Phases(1)->Composition()->SetValues(NComps,Liquid.Composition);

	thestream->Phases(0)->MolarEnthalpy()->SetValue(Vapour.Enthalpy);
	thestream->Phases(0)->MolarEntropy()->SetValue(Vapour.Entropy);
	thestream->Phases(0)->MolarDensity()->SetValue(Vapour.MolarDensity);
	thestream->Phases(0)->MolecularWeight()->SetValue(Vapour.MolecularWeight);
	thestream->Phases(0)->Composition()->SetValues(NComps,Vapour.Composition);
	
}