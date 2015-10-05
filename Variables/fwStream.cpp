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
	Z = new double[NComps];
	X = new double[NComps];
	Y = new double[NComps];
	Pressure=thestream->Pressure()->GetValue();
	Temperature = thestream->Temperature()->GetValue(); 
	Enthalpy = thestream->MolarEnthalpy()->GetValue();
	Entropy = thestream->MolarEntropy()->GetValue();

	X = thestream->Phases(1)->Composition()->GetValues();
	Y = thestream->Phases(0)->Composition()->GetValues();

	Z = thestream->Composition()->GetValues();
	NPhases = 2;
}
fwStream::~fwStream()
{
	
}
void fwStream::WriteStream(Stream* thestream)
{
	//opposite

	cout << X[0] << "\n";
	cout << X[1] << "\n";
	cout << X[2] << "\n";

	cout << Y[0] << "\n";
	cout << Y[1] << "\n";
	cout << Y[2] << "\n";

	thestream->Pressure()->SetValue(Pressure);
	thestream->Temperature()->SetValue(Temperature);
	thestream->MolarEnthalpy()->SetValue(Enthalpy);
	thestream->MolarEntropy()->SetValue(Entropy);
	thestream->Phases(1)->Composition()->SetValues(NComps,X);
	thestream->Phases(0)->Composition()->SetValues(NComps,Y);
	thestream->Composition()->SetValues(NComps, Z);
	NPhases = 2;
}