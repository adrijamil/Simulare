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
	void StreamSetup(string thecmd);
	SimCase* _activecase;
	void CaseSetup(string thesetupcmd);
};

