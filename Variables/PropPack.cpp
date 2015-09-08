#include "stdafx.h"
#include "PropPack.h"
#include "Ideal.h"
#include "RefPropPack.h"
#include <fstream>
#include <sstream>
using namespace std;

PropPack::PropPack()
{

}



void PropPack::AddComponent(string thecompname)
{
	//add component from D:\East101\Adri\devprojects\theSeed\Variables\Variables\ComponentDatabase.csv
	 Component* mycomp = new Component;
	string myline;
	string mystring;
	istringstream mystream;
	int err;
	int NComps, Nparams;
	int namesize;
	/*signed int namelen = thecompname.length() + 1;
	namelen = namelen*-1;*/
	long position;

	ifstream mycsv; //open for input
	//mycsv.open("ComponentDatabase.csv", ios::in);
	mycsv.open("D:/East101/Adri/devprojects/theSeed/Variables/Variables/ComponentDatabase.csv", ios::in);
	//mycsv.open("test.txt", ios::in);
	if (mycsv.is_open())
	{
		//get NComps and Nparams;
		getline(mycsv, mystring, ',');
		Nparams = atoi(mystring.c_str());
		getline(mycsv, mystring, ',');
		NComps = atoi(mystring.c_str());

		//skip params line
		getline(mycsv, myline);
		getline(mycsv, myline);

		cout<< "\n";
		position = mystream.cur;
		while (getline(mycsv, myline))
		{
			//cout << "\n";
			mystream.str(myline); //turn the line string into a stream
			getline(mystream, mystring, ','); //get element (ID)
			getline(mystream, mystring, ',');//get element (Name)
			cout << mystring << "\n";
			if (mystring == thecompname)
			{	
				//start again at begining of stream
				mystream.seekg(0);
	
				getline(mystream, mystring, ',');
				mycomp->ID = atoi(mystring.c_str());

				getline(mystream, mystring, ',');
				mycomp->Name = mystring;

				getline(mystream, mystring, ',');
				mycomp->Mw = atof(mystring.c_str());

				getline(mystream, mystring, ',');
				mycomp->Pc = atof(mystring.c_str());

				getline(mystream, mystring, ',');
				mycomp->Tc = atof(mystring.c_str());

				getline(mystream, mystring, ',');
				mycomp->Acentric = atof(mystring.c_str());

				mycsv.seekg(0,mycsv.end); //go to end to terminate while loop
			}
			position = mystream.cur;

		}
		mycsv.close();
	}


	_ncomps = _ncomps + 1; //update count
	Component* newcomps=new Component[_ncomps];

	//cout << sizeof(*mycomp) << "\n";
	//cout << sizeof(_components) << "\n";
	//realloc is similar to redim preserve. members of array are preserved and sent to new array (newchildren)
	//should be possible to reallocate straight to itself ie _children = (FSObject**)realloc(...... but this is safer. can catch errors.
	//_components = (Component*)realloc(_components, _ncomps* sizeof(*mycomp)); //allocate new array

	for (int k = 0; k < _ncomps - 1; k++)
	{
		newcomps[k] = _components[k];
	}

	newcomps[_ncomps-1] = *mycomp;
	//memcpy(mycomp, newcomps[_ncomps-1], sizeof *mycomp);

	 _components = new Component[_ncomps];
	//_components[_ncomps-1].Name = mycomp->Name;
	//_components[_ncomps - 1] = *mycomp;
	for (int k = 0; k < _ncomps ; k++)
	{
		_components[k] = newcomps[k];
		//_components[k].Name = newcomps[k].Name;
		//_components[k].ID = newcomps[k].ID;
		//_components[k].Acentric = newcomps[k].Acentric;
		//_components[k].Pc = newcomps[k].Pc;
		//_components[k].Tc = newcomps[k].Tc;
		//_components[k].Mw = newcomps[k].Mw;

	}

	//if (_components != NULL) //if it's null then realloc tak jadi
	//{
	//	//_components = newcomps;
	//	//memcpy(&mycomp, &_components[_ncomps - 1], sizeof(mycomp));
	//	//cout << _components[_ncomps - 1].Name;
	//	_components[_ncomps - 1].Name = mycomp->Name;
	//	_components[_ncomps - 1].ID = mycomp->ID;
	//	_components[_ncomps - 1].Mw = mycomp->Mw;
	//	_components[_ncomps - 1].Acentric = mycomp->Acentric;
	//	_components[_ncomps - 1].Pc = mycomp->Pc;
	//	_components[_ncomps - 1].Tc = mycomp->Tc;
	//}
	cout << _components[_ncomps - 1].Name;

}

void PropPack::SetMethod(FlashTypeEnum theFlashType)
{
	switch (theFlashType)
	{
	case IDEAL:
		_flashmethod = new Ideal;

		break;
	case REFPROP:
		_flashmethod = new RefPropPack;
		break;
	}
}


PropPack::~PropPack()
{
}

