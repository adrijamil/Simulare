#pragma once
class Stream;

class fwStream
{
public:
	fwStream();
	~fwStream();
	double Pressure;
	double Temperature;
	double VapourFraction;
	double Enthalpy;
	double Entropy;
	double* X;
	double* Y;
	double* Z;
	double densTot;
	double densL;
	double densV;
	int NPhases;
	int NComps;
	void ReadStream(Stream* thestream);
	void WriteStream(Stream* thestream);
};

