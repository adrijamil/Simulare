// ===============================
// AUTHOR     :		Adri
// CREATED(d/m/yy):	7/9/15
// PURPOSE     :	Subclass of FlashMethod such as Ideal and RefProp
//					used to apply strategy pattern to the PropPack class
//					PropPack class keeps a reference to this object to do flash calcs
// ===============================
// TO BE IMPLEMENTED: 
// 1. To keep relevant pure component data (Tc, Pc) on board so don't have too keep reaching into PropPack. Do this on the base class
// 2. Implement this as a singleton
// ===============================
// SPECIAL NOTES:	
// 1. 
// ===============================
// Change History: - put name, date and description of change
// 1. Created
//==================================
#ifndef __REFPROPPACK_H_INCLUDED__
#define __REFPROPPACK_H_INCLUDED__

#include <windows.h>
#include <stdio.h>
#include <iostream>


#include "FlashMethod.h"
#include "Stream.h"


using namespace std;
//can I put this constants here?
const long refpropcharlength = 255;
const long filepathlength = 255;
const long lengthofreference = 3;
const long errormessagelength = 255;
const long ncmax = 20;		// Note: ncmax is the max number of components
const long numparams = 72;
const long maxcoefs = 50;



class RefPropPack :
	public FlashMethod
{
public:
	RefPropPack();
	
	~RefPropPack();

	void Setup(PropPack* thePP);

	void PT_Flash(Stream* theStream, PropPack* thePP);
	void TQ_Flash(Stream* theStream, PropPack* thePP);
private:
	HMODULE RefProp_dll_instance;
	string _fluids_path;

};

#endif
