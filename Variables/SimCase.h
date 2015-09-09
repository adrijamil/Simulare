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
	SimCase(){
		_name = "MAIN"; 
		_default_package = 0;
		thePPBuilder = new PropPackBuilder;
	}

	template <class string, size_t N >
	void Setup(FlashTypeEnum flashmethod, string const (&components)[N])
	{
		int ncomps;
		ncomps =N;

		thePPBuilder->BuidPackage();
		
		for (int i = 0; i < 3; i++)
		{
			thePPBuilder->AddComponent(components[i]);
		}

		thePPBuilder->SetFlashMethod(flashmethod);
		_default_package = thePPBuilder->GetPackage();

	}


	Stream* Stream(string name)
	{
		return 0;
	}

	~SimCase();
private:
	PropPackBuilder* thePPBuilder;

	

};

#endif
