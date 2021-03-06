#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include "SimCase.h"
#include "PropPackBuilder.h"
#include "UnitOpBuilder.h"

class CommandInterpreter
{
public:
	CommandInterpreter();
	CommandInterpreter(string theinputfile);
	~CommandInterpreter();
	void SendCommand(string thecommand);
	void ReadInputFile(string thefilepath);
private:
	void OutputAll();
	void StreamSetup(string thename, string thespecs);
	SimCase* _activecase;
	void CaseSetup(string theflash, string thecomps);
//	void ValveSetup(string thename, string thespecs);
	//void HeaterSetup(string thename, string thespecs);
	void UnitOpSetup(string theop,string thename, string thespecs);

	PropPackBuilder* thePPBuilder=new PropPackBuilder;
	UnitOpBuilder* _theuobuilder = new UnitOpBuilder;
};

