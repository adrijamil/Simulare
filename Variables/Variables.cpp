// Variables.cpp : Defines the entry point for the console application.
//
// standard includes
#include "stdafx.h"
#include "RPManager.h"


// custom includes
//#include "BaseVariable.h"
//#include "RealVariable.h"
//#include "UnitConvertor.h"
//#include "Fluid.h"
//#include "SimCase.h"
#include "CommandInterpreter.h"


//#include "RefPropFunctions.h"

#include "FSObject.h"


#include "FlowSheet.h"

//namespace
using namespace std;

//global class
//UnitConvertor *UnitConvertor::s_instance = 0;

RPManager* RPManager::_instance = 0;

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

	//RealVariable rv;

	//double arr[3];
	//arr[0] = 0.1111;
	//arr[1] = 0.222;
	//arr[2] = 0.333;

	//rv.SetValue(arr);

	//double* ptr =  new double[3];

	//ptr = rv.GetValues();
	// 
	//cout << ptr[0];
	//cout << ptr[1];
	//cout << ptr[2];
	
	
//
//	Stream strm1;
//	strm1.Pressure()->SetValue(101.325);
//	strm1.Temperature()->SetValue(200);
//
//	double x[3];
//	x[0] = 0.333333333;
//	x[1] = 0.333333333;
//	x[2] = 0.333333333;
//	cout << "\n";
//	cout << "\n";
//	cout << x[1];
//
//	strm1.Composition()->SetValue(x);
//
//	PropPack myPP1;
//	myPP1.SetName("theone");
//	myPP1.SetMethod(IDEAL);
//	myPP1.AddComponent("METHANE");
//	myPP1.AddComponent("ETHANE");
//	myPP1.AddComponent("BENZENE");
//
//	strm1.SetPropertyPackage(&myPP1);
//	Stream strm2;
//	strm2.Pressure()->SetValue(101.325);
//	strm2.Temperature()->SetValue(200);
//	
//	double x2[3];
//	x2[0] = 0.333333333;
//	x2[1] = 0.333333333;
//	x2[2] = 0.333333333;
//	cout << "\n";
//	cout << "\n";
//	cout << x[1];
//	//xcheck = new double[3];
//
//	strm2.Composition()->SetValue(x2);
//
//
//	PropPack myPP2;
//	myPP2.SetName("thetwo");
//	myPP2.SetMethod(REFPROP);
//
//	myPP2.AddComponent("METHANE");
//	myPP2.AddComponent("ETHANE");
//	myPP2.AddComponent("BENZENE");
//	myPP2.Setup();
//
//	strm2.SetPropertyPackage(&myPP2);
//
//	bool dabool;
//
//FlowSheet fs1;
//
//fs1.Add(&strm1);
//fs1.Add(&strm2);
//dabool=fs1.Solve();


//SimCase mycase;
//string mycompstrings[3];
//mycompstrings[0] = "METHANE";
//mycompstrings[1] = "ETHANE";
//mycompstrings[2] = "BENZENE";
//
//double mycomps[3];
//mycomps[0] = 0.333333;
//mycomps[1] = 0.333333333;
//mycomps[2] = 0.333333333;
//
//mycase.Setup(REFPROP, mycompstrings);
//
//mycase.AddStream("strm1");
//mycase.GetStream("strm1")->Composition()->SetValue(mycomps);
//mycase.GetStream("strm1")->Pressure()->SetValue(101.325);
//mycase.GetStream("strm1")->Temperature()->SetValue(200);


CommandInterpreter mycase("inputfile2.txt");
//CommandInterpreter mycase;
string mycommand;
mycommand = "";
bool isexit=false;


while (!isexit)
{
	cin >> mycommand;
	if (mycommand == "EXIT")
	{
		isexit = true;
	}
	else
	{
		mycase.SendCommand(mycommand);
	}
	
}

cout << "Exiting. Press enter.";
	getchar();

	return 0;
}

