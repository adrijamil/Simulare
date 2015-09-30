#ifndef __SIMCASE_H_INCLUDED__
#define __SIMCASE_H_INCLUDED__

#include <iostream>

#include "FlowSheet.h"
#include "PropPackBuilder.h"

using namespace std;

class SimCase :
	public FlowSheet
{
public:
	SimCase(string thename){
		_casename = thename;

		_name = "MAIN"; 
		_default_package = 0;
		thePPBuilder = new PropPackBuilder;
	}

	template <class string, size_t N >
	void Setup(FlashMethodEnum flashmethod, string const (&components)[N])
	{
		int ncomps;
		ncomps =N;
		std::string thecomp;

		thePPBuilder->BuildPackage();
		
		for (int i = 0; i < 3; i++)
		{
			thecomp = components[i];
			if (thecomp.compare("none") != 0)
			{
				thePPBuilder->AddComponent(thecomp);
			}
			
		}

		thePPBuilder->SetFlashMethod(flashmethod);
		

		_default_package = thePPBuilder->GetPackage();

	}




	~SimCase();
private:
	PropPackBuilder* thePPBuilder;
	string _casename;

	

};

#endif
