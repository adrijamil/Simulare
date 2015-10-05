#pragma once
class Stream;

class fwStream
{
public:
	fwStream();
	fwStream(Stream* thestream);
	~fwStream();
	double Pressure;
	double Temperature;
	double* X;
	double* Y;
	double* Z;
	int NPhases;
};

