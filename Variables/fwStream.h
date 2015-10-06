#pragma once
class Stream;
#include "Phase.h"
struct fwPhase
{
	PhaseType PhaseName;
	double PhaseFraction;
	double Enthalpy;
	double Entropy;
	double* Composition;
	double MolarDensity;
	double MolecularWeight;
};


class fwStream
{
public:
	fwStream();
	~fwStream();
	double Pressure;
	double Temperature;
	double VapourFraction;
	//make phases as an array with names (enum)
	fwPhase Liquid;
	fwPhase Vapour;
	fwPhase Overall;

	fwPhase* Phase(PhaseType thephasename);
	fwPhase* Phase(int phasenumber);
	fwPhase* Phases;

	int NComps;

	void ReadStream(Stream* thestream);
	void WriteStream(Stream* thestream);
private:
	
};

