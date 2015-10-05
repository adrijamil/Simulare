#include "RPEnergyCalc.h"

typedef void(__stdcall *fp_THERMdllTYPE)(double &, double &, double *, double &, double &, double &, double &, double &, double &, double &, double &);
fp_THERMdllTYPE THERMdll;

RPEnergyCalc::RPEnergyCalc()
{
	THERMdll = (fp_THERMdllTYPE)GetProcAddress(RPManager::Instance()->hInstance(), "THERMdll");;
}

void RPEnergyCalc::Calculate()
{
	//fwStream* tempfwstrm = new fwStream;

	
	int ncomps = _parent->NComps();

	double t, d, p, e, h, s, cv, cp, w, hjt;
	double x[ncmax];

	t = _parent->RefStream()->Temperature;
	p = _parent->RefStream()->Pressure;

	for (int k = 0; k < ncomps; k++)
	{
		x[k] = _parent->RefStream()->Y[k];
	}

	THERMdll(t, d, x, p, e, h, s, cv, cp, w, hjt);
	_parent->RefStream()->Enthalpy=h;
	_parent->RefStream()->Entropy=s;

	for (int k = 0; k < ncomps; k++)
	{
		x[k] = _parent->RefStream()->Y[k];
	}

	THERMdll(t, d, x, p, e, h, s, cv, cp, w, hjt);
	_parent->RefStream()->Enthalpy = h;
	_parent->RefStream()->Entropy = s;
}

void RPEnergyCalc::_calcFluid(Fluid* thefluid)
{
	
}