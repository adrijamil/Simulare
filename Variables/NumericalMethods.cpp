#include "stdafx.h"
#include "NumericalMethods.h"


NumericalMethods::NumericalMethods()
{
	_myfx = 0;
}


//double NumericalMethods::Brent(Ideal* thePP, double ain, double bin)
//{
//	double fa, fb, fc, s, fs, c, d, tol;
//	bool mflag = 1;
//	tol = 0.00001;
//	int cond;
//	int iter = 0;
//	double temp;
//	double a = ain;
//	double b = bin;
//	//FUNC_PTR fx = thePP->_RR;
//	// instantiate myclass
//	FUNC_PTR fx = &Ideal::_RR;	// assign address
//	(*thePP.*fx) (123);
//
//	double retval = -32767;
//	fa = (*thePP.*fx)(a);
//	fb = (*thePP.*fx)(b);
//	if (fa*fb >= 0)
//	{
//		return retval;
//	}
//	if (abs(fa)<abs(fb))
//	{
//		temp = a;
//		a = b;
//		b = temp;
//
//		temp = fa;
//		fa = fb;
//		fb = temp;
//	}
//
//	c = a;
//	fc = _RR(c, x, ncomp);
//
//	double delta = 0;
//
//	d = 7;
//	fs = 7;
//	do
//	{
//		if (fa != fc&&fb != fc)
//		{
//			s = a*fb*fc / (fa - fb) / (fa - fc) + b*fa*fc / (fb - fa) / (fb - fc) + c*fb*fa / (fc - fa) / (fc - fb);
//		}
//		else
//		{
//			s = b - fb*(b - a) / (fb - fa);
//		}
//
//		cond = 0;
//		if (!inbetween(s, (3 * a + b) / 4, b))
//		{
//			cond = 1;
//
//		}
//		else if (mflag && abs(s - b) >= abs(b - c) / 2)
//		{
//			cond = 1;
//
//		}
//		else if (!mflag && abs(s - b) >= abs(c - d) / 2)
//		{
//			cond = 1;
//
//		}
//		else if (mflag && abs(b - c) <abs(delta))
//		{
//			cond = 1;
//
//		}
//		else if (!mflag && abs(c - d) <abs(delta))
//		{
//			cond = 1;
//
//		}
//		if (cond == 1)
//		{
//			s = (a + b) / 2;
//			mflag = 1;
//			std::cout << "brent take mid root: " << s << " iter: " << iter << "\n";
//
//		}
//		else
//		{
//			mflag = 0;
//		}
//
//		fs = _RR(s, x, ncomp);
//
//		d = c;
//		c = b;
//
//		if (fa*fs<0)
//		{
//			b = s;
//		}
//		else
//		{
//			a = s;
//
//		}
//
//
//
//		fa = _RR(a, x, ncomp);
//		fb = _RR(b, x, ncomp);
//		fc = _RR(c, x, ncomp);
//
//		if (abs(fa)<abs(fb))
//		{
//			temp = a;
//			a = b;
//			b = temp;
//
//			temp = fa;
//			fa = fb;
//			fb = temp;
//		}
//
//		iter++;
//	} while (abs(b - a) > tol || abs(fs) > tol);
//
//	std::cout << "brent root: " << s << " iter: " << iter << "\n";
//	return s;
//
//}
NumericalMethods::~NumericalMethods()
{
}
