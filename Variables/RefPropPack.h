#pragma once
#include "PropPack.h"

#include "Stream.h"
#include <windows.h>

#include <stdio.h>
#include <iostream>

//can I put this constants here?
const long refpropcharlength = 255;
const long filepathlength = 255;
const long lengthofreference = 3;
const long errormessagelength = 255;
const long ncmax = 20;		// Note: ncmax is the max number of components
const long numparams = 72;
const long maxcoefs = 50;



class RefPropPack :
	public PropPack
{
public:
	RefPropPack();
	
	~RefPropPack();

	void PT_Flash(Stream* thestream);

private:
	HINSTANCE RefProp_dll_instance;
	string _fluids_path;

};

