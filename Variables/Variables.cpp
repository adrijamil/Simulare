// Variables.cpp : Defines the entry point for the console application.
//
// standard includes
#include "stdafx.h"



// custom includes
//#include "BaseVariable.h"
//#include "RealVariable.h"
//#include "UnitConvertor.h"
//#include "Fluid.h"
#include "Stream.h"
#include "Ideal.h"
#include "RefPropPack.h"
//#include "RefPropFunctions.h"
//#include "PropPack.h"
//namespace
using namespace std;

//global class
//UnitConvertor *UnitConvertor::s_instance = 0;

int _tmain(int argc, _TCHAR* argv[])
{
	//BaseVariable<double> thebv;
	//double thedb;
	//thedb = 4;
	//double dbarr[3];
	//dbarr[0] = 0.2;
	//dbarr[1] = 0.3;
	//dbarr[2] = 0.8;
	//double* thptr = dbarr;
	//double dbarr2[2];
	//dbarr2[0] = 4;
	//dbarr2[1] = 8;
	//
	//thedb = 5; 
	////cout << sizeof(dbarr); //this is size of the array
	////cout << sizeof(*dbarr);// this size of an element


	//thebv.SetValue(dbarr);
	//cout << thebv.GetValue(0) << "\n";
	//cout << thebv.GetValue(1) << "\n";
	//cout << thebv.GetValue(2) << "\n";

	////thebv.SetValue(dbarr2);
	////cout << thebv.GetValue(0) << "\n";
	////cout << thebv.GetValue(1) << "\n";
	////cout << thebv.GetValue(2) << "\n";

  //*thptr = thebv.GetValue(); //I can obtain the pointer and deconstruct it back

	//dbarr2[0] = thptr[0];
	//dbarr2[1] = thptr[1];

	////cout << dbarr2[0] << "\n";
	//cout << thebv.GetValue(1);
	//cout << dbarr2[1] << "\n";

	 
	//UnitConvertor theconv2;

	//cout << thecon.get_value();

	//RealVariable RV(6.7);

	//BaseVariable<double> BV(thearr);
	//RealVariable RV2(thearr);
	//cout << RV2.GetValue(1) << "\n";


	//double comp[3];
	//comp[0] = 0.6;
	//comp[1] = 0.9;
	//comp[2] = 0.3;



	//double db1;
	//double* pt1;
	//double* pt2;

	//db1 = 3;
	//pt1 = &db1;
	//pt2 = pt1;

	//cout << *pt1 << "\n";
	//cout << *pt2 << "\n";

	//*pt1 = 4;

	//cout << *pt1 << "\n";
	//cout << *pt2 << "\n";

	RealVariable rv;

	double arr[3];
	arr[0] = 0.1111;
	arr[1] = 0.222;
	arr[2] = 0.333;

	rv.SetValue(arr);

	double* ptr =  new double[3];

	ptr = rv.GetValues();
	 
	cout << ptr[0];
	cout << ptr[1];
	cout << ptr[2];
	



	
	Stream strm1;
	/*Phase ph1;
	ph1.Pressure()->SetValue(0.3);
	cout << ph1.Pressure()->GetValue();
	RealVariable* rv;*/

	strm1.Pressure()->SetValue(101.325);
	strm1.Temperature()->SetValue(200);
	double* xcheck;
	double xout;
	double x[3];
	x[0] = 0.333333333;
	x[1] = 0.333333333;
	x[2] = 0.333333333;
	cout << "\n";
	cout << "\n";
	cout << x[1];
	xcheck = new double[3];

	strm1.Composition()->SetValue(x);


	//cout << strm1.Pressure()->GetValue()<< "\n";

	//double* x;
	//x = strm1.Phases(1)->Pressure()->GetValue();
	//PropPack myPP1;
	RefPropPack myPP1;

	myPP1.SetName("theone");
	//myPP2.SetName("theother");

	strm1.SetPropertyPackage(&myPP1);
	strm1.PTFlashMe();
	cout <<"\n" << "\n";
	cout << strm1.Phases(0)->Composition()->GetValue(0) << "\n";
	cout << strm1.Phases(0)->Composition()->GetValue(1)<<"\n";
	cout << strm1.Phases(0)->Composition()->GetValue(2) << "\n";
	cout << strm1.Phases(0)->PhaseMoleFraction()->GetValue() << "\n";
	getchar();

	return 0;
}

