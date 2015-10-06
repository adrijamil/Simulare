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
		x[k] = _parent->RefStream()->Vapour.Composition[k];
	}

	THERMdll(t, d, x, p, e, h, s, cv, cp, w, hjt);
	_parent->RefStream()->Vapour.Enthalpy=h;
	_parent->RefStream()->Vapour.Entropy = s;


	for (int k = 0; k < ncomps; k++)
	{
		x[k] = _parent->RefStream()->Liquid.Composition[k];
	}
	THERMdll(t, d, x, p, e, h, s, cv, cp, w, hjt);
	_parent->RefStream()->Liquid.Enthalpy = h;
	_parent->RefStream()->Liquid.Entropy = s;
	
}

void RPEnergyCalc::_calcFluid(Fluid* thefluid)
{
	
}