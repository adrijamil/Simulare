#pragma once
#include <iostream>
#include <fstream>
#include <sstream>

#include "SimCase.h"
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
	void ValveSetup(string thename, string thespecs);
	void HeaterSetup(string thename, string thespecs);
};

