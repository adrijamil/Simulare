// ===============================
// AUTHOR     :		Adri
// CREATED(d/m/yy):	7/9/15
// PURPOSE     :	Base class for other PropertyPackages such as Ideal and RefProp
//					Implements the strategy pattern for FlashMethod. can utilise this for other functions eg mixing rule
//					
//					
// TO BE IMPLEMENTED: 
// this class needs a factory.

// SPECIAL NOTES:	
// 1. Physical properties should be attached to property package I suppose.
// 2. Should include a setup method + issetup member. set the ncomps, define components etc.
// ===============================
// Change History: - put name, date and description of change
// 1. Created
//==================================




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
enum ComponentNameEnum  { METHANE, ETHANE,BENZENE };
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
	virtual void AddComponent(string thecompname);


	void SetName(string thename){ _name = thename; }
	int NComps(){ return _ncomps; }

	Component GetComponent(int i){ return _components[i]; }
	void Setup(){ _flashmethod->Setup(this); }
protected:
	string _name;
	Component* _components; //make it fixed first
	int _ncomps;
	FlashMethod* _flashmethod;
};



#endif
