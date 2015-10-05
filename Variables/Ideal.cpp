#include "stdafx.h"
#include "Ideal.h"



bool inbetween(double x, double a, double b)
{

	if (a < b)
	{
		double temp = a;
		a = b;
		b = temp;
	}

	if (x<a&&x>b)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//double Ideal::bisect(double ain, double bin, double *x, int ncomp)
//{
//	double fa, fb, fc, fs, c, tol;
//
//	tol = 0.00001;
//	int cond;
//	int iter = 0;
//	double temp;
//	double a = ain;
//	double b = bin;
//
//	double retval = -32767;
//	fa = _RR(a, x, ncomp);
//	fb = _RR(b, x, ncomp);
//
//	c = a;
//	fc = _RR(c, x, ncomp);
//
//
//
//	do
//	{
//
//		c = (a + b) / 2;
//		fc = _RR(c, x, ncomp);
//
//		if (fa*fc<0)
//		{
//			b = c;
//		}
//		else
//		{
//			a = c;
//
//		}
//
//
//
//		fa  =_RR(a, x, ncomp);
//		fb = _RR(b, x, ncomp);
//		
//
//		if (abs(fa)<abs(fb))
//			iter++;
//
//
//	} while (abs(b - a) > tol || abs(fc) > tol);
//
//	std::cout << "bisect root: " << c << " iter: " << iter << "\n";
//	return c;
//}


double Ideal::brent(FUNC_PTR fx, double ain, double bin, double *x, int ncomp)
{
	double fa, fb, fc, s, fs, c, d, tol;
	bool mflag = 1;
	tol = 0.00001;
	int cond;
	int iter = 0;
	double temp;
	double a = ain;
	double b = bin;

	

	double retval = -32767;
	fa = _RR(a, x, ncomp);
	fb = _RR(b, x, ncomp);
	if (fa*fb >= 0)
	{
		return retval;
	}
	if (abs(fa)<abs(fb))
	{
		temp = a;
		a = b;
		b = temp;

		temp = fa;
		fa = fb;
		fb = temp;
	}

	c = a;
	fc = _RR(c, x, ncomp);

	double delta = 0;

	d = 7;
	fs = 7;
	do
	{
		if (fa != fc&&fb != fc)
		{
			s = a*fb*fc / (fa - fb) / (fa - fc) + b*fa*fc / (fb - fa) / (fb - fc) + c*fb*fa / (fc - fa) / (fc - fb);
		}
		else
		{
			s = b - fb*(b - a) / (fb - fa);
		}

		cond = 0;
		if (!inbetween(s, (3 * a + b) / 4, b))
		{
			cond = 1;

		}
		else if (mflag && abs(s - b) >= abs(b - c) / 2)
		{
			cond = 1;

		}
		else if (!mflag && abs(s - b) >= abs(c - d) / 2)
		{
			cond = 1;

		}
		else if (mflag && abs(b - c) <abs(delta))
		{
			cond = 1;

		}
		else if (!mflag && abs(c - d) <abs(delta))
		{
			cond = 1;

		}
		if (cond == 1)
		{
			s = (a + b) / 2;
			mflag = 1;
			std::cout << "brent take mid root: " << s << " iter: " << iter << "\n";

		}
		else
		{
			mflag = 0;
		}

		fs = _RR(s, x, ncomp);

		d = c;
		c = b;

		if (fa*fs<0)
		{
			b = s;
		}
		else
		{
			a = s;

		}



		fa = _RR(a, x, ncomp);
		fb = _RR(b, x, ncomp);
		fc = _RR(c, x, ncomp);

		if (abs(fa)<abs(fb))
		{
			temp = a;
			a = b;
			b = temp;

			temp = fa;
			fa = fb;
			fb = temp;
		}

		iter++;
	} while (abs(b - a) > tol || abs(fs) > tol);

	std::cout << "brent root: " << s << " iter: " << iter << "\n";
	return s;
}




//calculate RR equation
double Ideal::_RR(double vfrac, double *comps, int NComp)
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

	double vfrac;

	int iter; 
	int maxiter;
	double* Zi;
	double* Yi;
	double* Xi;
	int ncomp = thePP->NComps();
	maxiter = 1000;
	

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
	
	vfrac = _solveRR( Zi, ncomp);
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

double Ideal::_solveRR(double* comps, int NComp)
{
	double hi = 1;
	double lo = 0;
	double mid;

	//double (Ideal::*fx)(double vfrac, double* comps, int NComp) = &Ideal::_RR;;
	FUNC_PTR func= &Ideal::_RR;
	mid = brent(func,hi, lo, comps, NComp);
	

	return mid;

}

double Ideal::_solveforVf(double P, double* comps, int NComp)
{
	double retval;
	retval = _solveRR(comps, NComp);
	return retval;
}


void Ideal::TQ_Flash(Stream* theStream, PropPack* thePP)
{
	//use secant
	//if Vf=1 then first guess=Pvap lowest
	//if Vf=0 then first guess=Pvap highest
	//else interpolate
	double* Zi;
	int ncomp;
	ncomp = thePP->NComps();
	double Pvaphigh, Pvaplow, Pvap, T, Tr, Vfspec, P, VfCalc_1, VfCalc_2, P_1,P_2;
	int Niter = 0;
	double hi = 1;
	double lo = 0;
	double mid = 0.5;

	double* Yi;
	double* Xi;
	Xi = new double[ncomp];
	Yi = new double[ncomp];

	double fhi;
	double flo;
	double fmid;
	T = theStream->Temperature()->GetValue();
	Vfspec = theStream->VapourFraction()->GetValue();
	Pvaplow = 1e10;
	Pvaphigh = -1e10;
	double delta, tol;
	delta = 100;
	tol = 0.01;
	Zi = new double[ncomp];
	Zi = theStream->Composition()->GetValues();

	for (int i = 0; i < ncomp; i++)
	{
		Tr = T / thePP->GetComponent(i).Tc;
		Pvap = thePP->GetComponent(i).Pc*(exp(5.92714 - 6.09648 / Tr - 1.28862*log(Tr) + 0.169347*pow(Tr, 6) + thePP->GetComponent(i).Acentric*(15.2518 - 15.6875 / Tr - 13.4721*log(Tr) + 0.43577*pow(Tr, 6))));

		if (Pvap > Pvaphigh)
		{
			Pvaphigh = Pvap;
		}
		if (Pvap < Pvaplow)
		{
			Pvaplow = Pvap;
		}
	}
	hi = Pvaphigh;
	lo = Pvaplow;
	mid = (hi + lo) / 2;

	FUNC_PTR fx = &Ideal::_solveforVf;
	brent(fx, hi, lo, Xi,ncomp);

//	VfCalc_1 = Vfspec;
	while (delta > tol)
	{
		_calcKis(hi, T);
		fhi = _solveRR(Zi, ncomp) - Vfspec;

		_calcKis(lo, T);
		flo = _solveRR(Zi, ncomp) - Vfspec;

		_calcKis(mid, T);
		fmid = _solveRR(Zi, ncomp) - Vfspec;

		if ((fhi*fmid) > 0) //if fmid and fhi same sign
		{
			hi = mid;
		}
		else
		{
			lo = mid;
		}
		mid = (hi + lo) / 2;
		delta = abs(hi - lo);

		Niter = Niter + 1;

		

	}
	P = mid;


	for (int i = 0; i < ncomp; i++)
	{

		Xi[i] = Zi[i] / (1 + Vfspec*(_Ki[i] - 1));

		theStream->Phases(1)->Composition()->SetValue(i, Xi[i]);
		theStream->Phases(0)->Composition()->SetValue(i, _Ki[i] * Xi[i]);
	}



	//put it into the stream
	theStream->Pressure()->SetValue(P);


}

void Ideal::_calcKis(double p, double t)
{
	int ncomp;
	ncomp = _proppack->NComps();
	double Tr;
	double Pvap;


	for (int i = 0; i < ncomp; i++)
	{
		Tr = t / _proppack->GetComponent(i).Tc;
		//this is the Lee-Kesler method 
		Pvap = _proppack->GetComponent(i).Pc*(exp(5.92714 - 6.09648 / Tr - 1.28862*log(Tr) + 0.169347*pow(Tr, 6) + _proppack->GetComponent(i).Acentric*(15.2518 - 15.6875 / Tr - 13.4721*log(Tr) + 0.43577*pow(Tr, 6))));
		_Ki[i] = Pvap / p;
		//cout << _Ki[i]<< "\n";
	}

}

bool Ideal::Setup(PropPack* thePP)
{
	_proppack = thePP;
	return true;

}

void Ideal::Flash(Stream* theStream, PropPack* thePP, FlashTypeEnum theflashtype)
{
	if (theflashtype == PT)
	{
		PT_Flash(theStream, thePP);

	}
	else if (theflashtype = TQ)
	{
		TQ_Flash(theStream, thePP);
	}

}
Ideal::~Ideal()
{
}


