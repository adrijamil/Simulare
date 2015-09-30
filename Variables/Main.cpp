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
#include "FSObject.h"
#include "FlowSheet.h"
#include "ErrorLogger.h"
//global instance of ExceptionHandler;


//namespace
using namespace std;

//global class
//UnitConvertor *UnitConvertor::s_instance = 0;

ErrorLogger *ErrorLogger::s_instance = 0;
RPManager* RPManager::_instance = 0;

int _tmain(int argc, _TCHAR* argv[])
{
	ErrorLogger* glogger = ErrorLogger::Instance();
CommandInterpreter mycase("inputfile2.txt");
//CommandInterpreter mycase;
string mycommand;
mycommand = "";
bool isexit=false;

glogger->Spit();
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
