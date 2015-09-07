

//Physical properties should be attached to property package I suppose.
//Should include a setup method + issetup member. set the ncomps, define components etc.



//option 1: this class knows what a "Stream" is. Stream is "unpacked", flash is solved and stream is changed accordingly
//		this kinda violates encapsulation
//		

//option 2: this class does not know what a "Stream" is. He just gets inputs (P,T,x) and sends outputs. Stream changes itself accordingly.
//		this will load alot of functions to the stream.
//		stream needs to figure out which flash to call. this makes sense.

//lets try option 1. Keep all stream operations in this module with actual calc done by subclass

#ifndef __PROPPACK_H_INCLUDED__
#define __PROPPACK_H_INCLUDED__

#include <iostream>
#include <string>
#include "FlashMethod.h"

using namespace std;

class Stream;


struct Component
{
	string Name;
	int ID;
	double Mw;
	double Tc;
	double Pc;
	double Acentric;
};

enum FlashTypeEnum  {IDEAL,REFPROP};

using namespace std;
//template<typename T = Stream>
class PropPack
{
public:
	 PropPack();
	~PropPack();
	void SetMethod(FlashTypeEnum theFlashType);
	virtual void PT_Flash(Stream* thestream)
		{
			_flashmethod->PT_Flash(thestream,this);
		};// i need P, T and x. Output H, vf and a bunch of props.

	void SetName(string thename){ _name = thename; }
	int NComps(){ return _ncomps; }
	Component GetComponent(int i){ return _components[i]; }

protected:
	string _name;
	Component _components[3]; //make it fixed first
	int _ncomps;
	FlashMethod* _flashmethod;
};



#endif
