// ===============================
// AUTHOR     :		Adri
// CREATED(d/m/yy):	2/9/15
// PURPOSE     :	This a base class for Stream and Phase. They have common properties suvh as composition and pressure
//					Also Streams will have members of phases 
//					Should not need a name as it will not exist alone (or at all as a fluid object except in the implementation of subclasses)
//					Normalise method is included for testing. May not actually
//
// TO BE IMPLEMENTED: 
// 1. Copy/clone function
// SPECIAL NOTES:	
// 1. 
// ===============================
// Change History: - put name, date and description of change
// 1. Created
//==================================

#ifndef __FLUID_H_INCLUDED__
#define __FLUID_H_INCLUDED__

#include "RealVariable.h"

using namespace std;

class Fluid
{
public:
	Fluid();
	~Fluid();
	void Normalise();
	RealVariable* Pressure(){ return _pressure; };
	RealVariable* Composition(){ return _composition; };
	int NComponents;
	
protected:
	RealVariable* _composition = new RealVariable;

	// keep a reference.then when building the stream can just connect(ie stream pressure refers to phase pressure as well)
	//all these fuckers will be initialised by the stream object (phases and stream members point to the same variables). 
	string _BD_name;
	RealVariable* _pressure;
	RealVariable* _temperature;
	RealVariable* _mass_flow_rate;
	RealVariable* _massenthalpy;
	RealVariable* _physprops; // keep this as an array to be filled by another class (not the thermo engine)
	int* _proppack; //keep a reference to a property package object. make it later. 

};

#endif