#include "stdafx.h"
#include "CommandInterpreter.h"

using namespace std;

CommandInterpreter::CommandInterpreter(string theinputfile)
{
	string mystring;
	string str1, str2, str3, str4;

	fstream myfile;
	string mylongstring;

	bool isdone;
	isdone = false;
	//std::stringstream  mypartstream;
	myfile.open(theinputfile);
	while (myfile.good())
	{
		getline(myfile, mystring);
		if (mystring == "PROPPACK") //go into parsing for proppack setup
		{
			getline(myfile, str1);//this will be flash method
			getline(myfile, str2);//this will be components
			str2.append(",DONE");
			CaseSetup(str1, str2);
		}

		else if (mystring == "STREAM")
		{
			getline(myfile, str1);//this will be the name
			do
			{
				getline(myfile, str2);
				if (str3 != "")
				{
					str3.append("\n");
				}
				str3.append(str2);
				
			} while (str2!="");
			str3.append("DONE");
			StreamSetup(str1, str3);
			str3 = "";

		}
		else if (mystring == "VALVE" || mystring == "HEATER" || mystring == "MIXER" || mystring == "SPLITTER")
		{
			getline(myfile, str1);//this will be the name
			do
			{
				getline(myfile, str2);
				if (str3 != "")
				{
					str3.append("\n");
				}
				str3.append(str2);

			} while (str2 != "");
			str3.append("DONE");
			UnitOpSetup(mystring,str1, str3);
			str3 = "";

		}
	}

	_activecase->Solve();
	_activecase->Output();

	myfile.close();
	//rapidxml serial;

}
CommandInterpreter::CommandInterpreter()
{ 
	CaseSetup("","");

}


CommandInterpreter::~CommandInterpreter()
{


}


void CommandInterpreter::SendCommand(string thecommand)
{
	string myreply;
	string strname;
	if (thecommand == "ADDSTREAM")
	{
		StreamSetup("","");
	}
	else if (thecommand == "OUTPUT")
	{
		OutputAll();
	}
	else if (thecommand == "SOLVE")
	{
		_activecase->Solve();
	}
	else if (thecommand == "ADDUNITOP")
	{
		UnitOpSetup("", "", "");
	}
	else if (thecommand == "HELP")
	{
		cout << "COMMANDS AVAILABLE ARE: ADDSTREAM, ADDUNITOP, SOLVE, OUTPUT \n";
	}
	else
	{
		cout << thecommand << "? DOES NOT COMPUTE.\n";
	}
}


void CommandInterpreter::ReadInputFile(string thefilepath)
{

}

void CommandInterpreter::OutputAll()
{
	_activecase->Output();

}


void CommandInterpreter::CaseSetup(string theflash, string thecomps)
{
	
	string reply;

	//create new case by default
	//make option to load case
	//string* compnames;
	string compnames[20];
	std::istringstream  mypartstream(thecomps);
	int ncomps;
	//std::istringstream  mypartstream(thesetupcmd);
	for (int k = 0; k < 20; k++)
	{
		compnames[k] = "none";
	}

	thePPBuilder->BuildPackage();

	_activecase = new SimCase("Case1");
	bool issetup = false;
	std::cout << "Setting up property package.\n";
	
	while (!issetup)
	{
		if (theflash == "")
		{
			cout << "Select IDEAL or REFPROP: \n";
			cin >> theflash;
		}

		if (theflash == "IDEAL")
		{
			cout << "IDEAL selected.\n";
			thePPBuilder->SetFlashMethod(IDEAL);
			issetup = true;
		}
		else if (theflash == "REFPROP")
		{
			cout << "REFPROP selected.\n";
			thePPBuilder->SetFlashMethod(REFPROP);
			issetup = true;

		}
		else if (reply == "exit")
		{
			cout << "I give up.\n";
			issetup = true;
		}

		else
		{
			cout << "Does not compute.\n";
		}
	}

	issetup = false;
	ncomps = 0;
	while (!issetup)
	{
		
		if (thecomps == "")
		{
			cout << "Add a component. All caps please. \n";
			cin >> reply;
		}
		else
		{
			getline(mypartstream, reply,',');
		}

		if (reply == "DONE")
		{
			issetup = true;
		}
		else
		{ 
			thePPBuilder->AddComponent(reply);
		ncomps = ncomps + 1;
		cout << reply << " has been added. Add another component or enter DONE to finish \n";
		}
	}

	_activecase->SetPropPack(thePPBuilder->GetPackage());
	cout << "Case has been setup. \n";
}


void CommandInterpreter::StreamSetup(string thename, string thespecs)
{
	int myncomps;
	
	int i;
	bool issetup;
	
	double tempdb;
	std::istringstream  mypartstream(thespecs);
	
	string param;
	string thevar;
	
	issetup = false;
	//set stream name
	if (thename == "")
	{
		cout << "Enter stream name \n";
		cin >> thename;
	}

	_activecase->AddStream(thename); //default proppack will be used
	myncomps = _activecase->GetStream(thename)->NComps();
	double* molecomps = new double[myncomps];

	while (issetup==false)
	{
		if (thespecs != "")
		{
			getline(mypartstream, param, ' ');
		}
		else
		{
			cout << "Enter specs: PRESSURE, TEMPERATURE, COMPOSITION, VAPOURFRACTION, ENTHALPY, MASSFLOW OR DONE \n";
			cin >> param;

		}

		if (param == "PRESSURE")
		{
			if (thespecs != "")
			{
				getline(mypartstream, thevar);
			}
			else
			{
				cout << "Enter pressure in kPa \n";
				cin >> thevar;
			}
		
			tempdb = stod(thevar);
			_activecase->GetStream(thename)->Pressure()->SetValue(tempdb);
			_activecase->GetStream(thename)->Pressure()->IsCalculated(false);
		}
		else if (param == "TEMPERATURE")
		{	
			if (thespecs != "")
			{
				getline(mypartstream, thevar);
			}
			else
			{
				cout << "Enter temperature in Kelvin \n";
				cin >> thevar;
			}
			
			tempdb = stod(thevar);
			_activecase->GetStream(thename)->Temperature()->SetValue(tempdb);
			_activecase->GetStream(thename)->Temperature()->IsCalculated(false);

		}
		else if (param == "VAPOURFRACTION")
		{
			if (thespecs != "")
			{
				getline(mypartstream, thevar);
			}
			else
			{
				cout << "Enter vapour fraction (molar) (0 - 1) \n";
				cin >> thevar;
			}

			tempdb = stod(thevar);
			_activecase->GetStream(thename)->VapourFraction()->SetValue(tempdb);
			_activecase->GetStream(thename)->VapourFraction()->IsCalculated(false);

		}
		else if (param == "COMPOSITION")
		{	
			if (thespecs != "")
			{
				getline(mypartstream, thevar);
			}
			else
			{
				cout << "Enter molar composition. eg 0.2,0.3,0.5 \n";
				cin >> thevar;
			}
			std::istringstream  compstream(thevar);
			i = 0;
				while (compstream.good())
				{
					getline(compstream, thevar,',');
					molecomps[i] = stod(thevar);
					i = i + 1;
				}
				_activecase->GetStream(thename)->Composition()->SetValues(myncomps, molecomps);
				_activecase->GetStream(thename)->Composition()->IsCalculated(false);
				_activecase->GetStream(thename)->Normalise();
		}
		else if (param == "ENTHALPY")
		{
			if (thespecs != "")
			{
				getline(mypartstream, thevar);
			}
			else
			{
				cout << "Enter molar enthalpy in J/mol \n";
				cin >> thevar;
			}

			tempdb = stod(thevar);
			_activecase->GetStream(thename)->MolarEnthalpy()->SetValue(tempdb);
			_activecase->GetStream(thename)->MolarEnthalpy()->IsCalculated(false);

		}
		else if (param == "ENTROPY")
		{
			if (thespecs != "")
			{
				getline(mypartstream, thevar);
			}
			else
			{
				cout << "Enter molar entropy in J/mol \n";
				cin >> thevar;
			}

			tempdb = stod(thevar);
			_activecase->GetStream(thename)->MolarEntropy()->SetValue(tempdb);
			_activecase->GetStream(thename)->MolarEntropy()->IsCalculated(false);

		}
		else if (param == "MASSFLOW")
		{
			if (thespecs != "")
			{
				getline(mypartstream, thevar);
			}
			else
			{
				cout << "Enter mass flow kg/h \n";
				cin >> thevar;
			}

			tempdb = stod(thevar);
			_activecase->GetStream(thename)->MassFlow()->SetValue(tempdb);
			_activecase->GetStream(thename)->MassFlow()->IsCalculated(false);

		}
		else if (param == "DONE")
		{
			issetup = true;
		}
	}
	cout << thename << " has been added.\n";


}

void CommandInterpreter::UnitOpSetup(string theop, string thename, string thespecs)
{
	//string myreply;
	//string strname;
	
	if (theop == "")
	{
		cout << "Enter unit operation : VALVE, HEATER \n";
		cin >> theop;
	}

	if (theop == "VALVE")
	{
		_theuobuilder->BuildUnitOp(VALVE);
	}
	else if (theop == "HEATER")
	{
		_theuobuilder->BuildUnitOp(HEATER);
	}
	else if (theop == "MIXER")
	{
		_theuobuilder->BuildUnitOp(MIXER);
	}
	else if (theop == "SPLITTER")
	{
		_theuobuilder->BuildUnitOp(SPLITTER);
	}
	bool issetup;

	double tempdb;
	std::istringstream  mypartstream(thespecs);

	string param;
	string thevar;

	issetup = false;
	//set stream name
	if (thename == "")
	{
		cout << "Enter unit op name \n";
		cin >> thename;
	}


	_theuobuilder->SetName(thename);
	//connect inlet
	if (thespecs != "")
	{
		getline(mypartstream, param, '\n');
	}
	else
	{
		cout << "Enter inlet stream(s) name. eg. Strm1,Strm2 \n";
		cin >> param;
	}

	std::istringstream  streamstreami(param);
	while (streamstreami.good())
	{
		getline(streamstreami, param, ',');
		_theuobuilder->Connect(_activecase->GetStream(param), INLET);
	}


	//connect outlet
	if (thespecs != "")
	{
		getline(mypartstream, param, '\n');
	}
	else
	{
		cout << "Enter outlet stream(s) name. eg. Strm1,Strm2  \n";
		cin >> param;
	}

	std::istringstream streamstreamo(param);
	while (streamstreamo.good())
	{
		getline(streamstreamo, param, ',');
		_theuobuilder->Connect(_activecase->GetStream(param), OUTLET);
	}

	while (issetup == false)
	{

		if (thespecs != "")
		{
			getline(mypartstream, param, ' ');
		}
		else
		{
			if (theop == "VALVE")
			{
				cout << "Enter specs: K, PRESSUREDROP OR DONE \n";
			}
			else if (theop == "HEATER")
			{
				cout << "Enter specs: K, PRESSUREDROP, HEATINPUT OR DONE \n";
			}
			
			cin >> param;
		}

		if (param == "K")
		{
			if (thespecs != "")
			{
				getline(mypartstream, thevar);
			}
			else
			{
				cout << "Enter k in kpa-kg/h \n";
				cin >> thevar;
			}

			tempdb = stod(thevar);

			_theuobuilder->SpecifyVariable(K_RESISTANCE, tempdb);
		}
		else if (param == "PRESSUREDROP")
		{
			if (thespecs != "")
			{
				getline(mypartstream, thevar);
			}
			else
			{
				cout << "Enter k in kpa-kg/h \n";
				cin >> thevar;
			}

			tempdb = stod(thevar);
			_theuobuilder->SpecifyVariable(PRESSUREDROP, tempdb);
		}
		else if (param == "HEATINPUT")
		{
			if (thespecs != "")
			{
				getline(mypartstream, thevar);
			}
			else
			{
				cout << "Enter Q in W \n";
				cin >> thevar;
			}

			tempdb = stod(thevar);
			_theuobuilder->SpecifyVariable(HEATINPUT, tempdb);
		}
		else if (param == "DONE")
		{
			issetup = true;
		}
	}
	_activecase->AddUnitOp(_theuobuilder->GetUnitOp());

	cout << thename << " has been added.\n";


}