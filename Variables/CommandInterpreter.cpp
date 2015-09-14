#include "stdafx.h"
#include "CommandInterpreter.h"

CommandInterpreter::CommandInterpreter(string theinputfile)
{
	string mystring;
	fstream myfile;
	string mylongstring;

	bool isdone;
	isdone = false;
	//std::stringstream  mypartstream;
	myfile.open(theinputfile);
	while (isdone == false)
	{
		getline(myfile, mystring);
		if (mystring == "DONE")
		{
			isdone = true;
			mylongstring.append("DONE");
			mylongstring.append("\n");
		}

		if (isdone == false)
		{

			mylongstring.append(mystring);
			mylongstring.append("\n");
		}
	}

	CaseSetup(mylongstring);
	mylongstring = "";

	getline(myfile, mystring);//skip "STREAMS"
	while (getline(myfile, mystring))
	{
		//getline(myfile, mystring);
		if (mystring == "DONE")
		{
			StreamSetup(mylongstring);
			mylongstring = "";
			
		}
		else
		{

			mylongstring.append(mystring);
			mylongstring.append("\n");
		}
	}

	myfile.close();
	//rapidxml serial;

}
CommandInterpreter::CommandInterpreter()
{ 
	CaseSetup("NONE");
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
		StreamSetup("NONE");
	}
	else if (thecommand == "OUTPUT")
	{
		OutputAll();
	}
}


void CommandInterpreter::ReadInputFile(string thefilepath)
{

}

void CommandInterpreter::OutputAll()
{
	_activecase->Output();

}


void CommandInterpreter::CaseSetup(string thesetupcmd)
{
	
	string reply;
	FlashTypeEnum theflashtype;
	//create new case by default
	//make option to load case
	//string* compnames;
	string compnames[20];

	int ncomps;
	std::istringstream  mypartstream(thesetupcmd);
	for (int k = 0; k < 20; k++)
	{
		compnames[k] = "none";
	}


	_activecase = new SimCase("Case1");
	bool issetup = false;
	cout << "Setting up property package.\n";

	while (!issetup)
	{
		if (thesetupcmd == "NONE")
		{
			cout << "Select IDEAL or REFPROP: \n";
			cin >> reply;
		}
		else
		{
			getline(mypartstream, reply);
		}

		if (reply == "IDEAL")
		{
			cout << "IDEAL selected.\n";
			theflashtype = IDEAL;
			issetup = true;
		}
		else if (reply == "REFPROP")
		{
			cout << "REFPROP selected.\n";
			theflashtype = REFPROP;
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
		
		
		if (thesetupcmd == "NONE")
		{
			cout << "Add a component. All caps please. \n";
			cin >> reply;
		}
		else
		{
			getline(mypartstream, reply);
		}

		if (reply == "DONE")
		{
			issetup = true;
		}
		else
		{ 

		compnames[ncomps] = reply;
		ncomps = ncomps + 1;
		//FSObject** newchildren;
		cout << reply << " has been added. Add another component or enter DONE to finish \n";
		}
	}


	_activecase->Setup(theflashtype, compnames);

	cout << "Case has been setup. \n";
}


void CommandInterpreter::StreamSetup(string thecmd)
{
	string myreply;
	string strname;
	
	int myncomps;
	double tempdb;
	std::istringstream  mypartstream(thecmd);


	//set stream name
	if (thecmd == "NONE")
	{
		cout << "Enter stream name";
		cin >> strname;
	}
	else
	{
		getline(mypartstream, strname);
	}
	_activecase->AddStream(strname); //default proppack will be used


	myncomps = _activecase->GetStream(strname)->NComps();
	//double* molecomps = new double[myncomps];
	double* molecomps =new double[myncomps];
	//molecomps = (double*)realloc(molecomps, sizeof(*molecomps)*myncomps);
	 //*molecomps = new double[myncomps];
		for (int i = 0; i < myncomps; i++)
		{
			if (thecmd == "NONE")
			{
				cout << "Enter composition for component" << i + 1;
				cin >> myreply;
			}
			else
			{
				getline(mypartstream, myreply);
			}
			
			molecomps[i] = stod(myreply);
			//_activecase->GetStream(strname)->Composition()->SetValue(i,molecomps[i]);
		}

		_activecase->GetStream(strname)->Composition()->SetValues(myncomps, molecomps);
		_activecase->GetStream(strname)->Composition()->IsCalculated(false);

		
		_activecase->GetStream(strname)->Normalise();

		if (thecmd == "NONE")
		{
			cout << "Enter temperature in Kelvin";
			cin >> myreply;
		}
		else
		{
			getline(mypartstream, myreply);
		}

		tempdb = stod(myreply);
		_activecase->GetStream(strname)->Temperature()->SetValue(tempdb);
		_activecase->GetStream(strname)->Temperature()->IsCalculated(false);


		if (thecmd == "NONE")
		{
			cout << "Enter pressure in kPa";
			cin >> myreply;
		}
		else
		{
			getline(mypartstream, myreply);
		}
		tempdb = stod(myreply);
		_activecase->GetStream(strname)->Pressure()->SetValue(tempdb);
		_activecase->GetStream(strname)->Pressure()->IsCalculated(false);

		cout << "Stream Added";
		_activecase->Solve();
		_activecase->GetStream(strname)->Output();

}