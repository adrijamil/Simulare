#include "RPEnergyCalc.h"

typedef void(__stdcall *fp_THERMdllTYPE)(double &, double &, double *, double &, double &, double &, double &, double &, double &, double &, double &);
fp_THERMdllTYPE THERMdll;

RPEnergyCalc::RPEnergyCalc()
{
	THERMdll = (fp_THERMdllTYPE)GetProcAddress(RPManager::Instance()->hInstance(), "THERMdll");;
}
void RPEnergyCalc::Calculate(Stream* thestream)
{
	_calcFluid(thestream->Phases(0));
	_calcFluid(thestream->Phases(1));
}

void RPEnergyCalc::_calcFluid(Fluid* thefluid)
{
	int ncomps = _parent->NComps();

	double t, d, p, e, h, s, cv, cp, w, hjt;
	double x[ncmax];

	t = thefluid->Temperature()->GetValue();
	p = thefluid->Pressure()->GetValue();

	for (int k = 0; k < ncomps; k++)
	{
		x[k] = thefluid->Composition()->GetValue(k);
	}

	THERMdll(t, d, x, p, e, h, s, cv, cp, w, hjt);
	thefluid->MolarEnthalpy()->SetValue(h);
	thefluid->MolarEntropy()->SetValue(s);
}