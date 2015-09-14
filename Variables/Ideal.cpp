#include "stdafx.h"
#include "Ideal.h"

//calculate RR equation
double Ideal::_RR(double vfrac, double* comps,int NComp)
{
	double sum;
	sum = 0;
	//cout << "\n";
	//cout << comps[2];

	for (int i = 0; i < NComp; i++)
	{
		sum = sum+(comps[i] * (_Ki[i] - 1)) / (1 + vfrac*(_Ki[i] - 1));
	//	cout << comps[i] << "\n";
	}
	return sum;
}

//PT flash algorithm
void Ideal::PT_Flash(Stream* theStream, PropPack* thePP)
{
	double P;
	double T;
	double Pvap;
	
	double Tr;
	double tol;
	double delta;
	
	double hi;
	double lo;
	double mid;

	double fhi;
	double flo;
	double fmid;
	
	double vfrac;

	int iter; 
	int maxiter;
	double* Zi;
	double* Yi;
	double* Xi;
	int ncomp = thePP->NComps();
	maxiter = 1000;
	delta = 100;
	tol = 0.01;

	//get stream inputs
	P = theStream->Pressure()->GetValue();
	T = theStream->Temperature()->GetValue();
	

	//total composition
	Zi = new double[ncomp];
	Zi = theStream->Composition()->GetValues();
	//cout << "\n";
	//cout << Zi[0] << "\n";
	//cout << Zi[1] << "\n";
	//cout << Zi[2] << "\n";

	//phase composition
	Xi = new double[ncomp];
	Yi = new double[ncomp];

	//K values
	_Ki = new double[ncomp];

	//calculcate vapour pressures
	//calculate Ks
	for (int i = 0; i < ncomp; i++)
	{
		Tr = T / thePP->GetComponent(i).Tc;
		//this is the Lee-Kesler method 
		Pvap = thePP->GetComponent(i).Pc*(exp(5.92714 - 6.09648 / Tr - 1.28862*log(Tr) + 0.169347*pow(Tr, 6) + thePP->GetComponent(i).Acentric*(15.2518 - 15.6875 / Tr - 13.4721*log(Tr) + 0.43577*pow(Tr, 6))));
		_Ki[i] = Pvap / P;
		//cout << _Ki[i]<< "\n";
	}
	


	//solve Rachford-Rice equation using bisection
	//could lump procedures like this into a library
	//cout << _Ki[0] << " " << _Ki[1] << " " << _Ki[2];

	hi = 1;
	lo = 0;
	mid = 0.5;

	iter = 0;
	while (delta > tol)
	{
		fhi = _RR(hi, Zi, ncomp);
		flo = _RR(lo, Zi, ncomp);
		fmid = _RR(mid, Zi, ncomp);

	//	cout << iter << "\n" << "\n";
	//	cout << hi << " " << lo << " " << mid << "\n";
		//cout << fhi << " " << flo << " " << fmid;

		if ((fhi*fmid) > 0) //if fmid and fhi same sign
		{
			hi = mid;
		}
		else
		{
			lo = mid;
		}
		mid = (hi + lo) / 2;
		delta =abs(hi - lo);
		
		iter = iter + 1;
	}
	
	vfrac = mid;
	//cout << "calculated vfrac = " << mid;


	//calculate phase compositions
	for (int i = 0; i < ncomp; i++)
	{

		Xi[i] = Zi[i]/(1+vfrac*(_Ki[i]-1));
		//cout << Xi[i] << "\n";

		theStream->Phases(1)->Composition()->SetValue(i, Xi[i]);
		theStream->Phases(0)->Composition()->SetValue(i, _Ki[i] * Xi[i]);
		//Yi[i] = _Ki[i] * Xi[i];
	}



	//put it into the stream
	theStream->Phases(0)->PhaseMoleFraction()->SetValue(vfrac);
	theStream->Phases(1)->PhaseMoleFraction()->SetValue(1 - vfrac);

}



Ideal::~Ideal()
{
}
