#pragma once



//#include "PropPack.h"
using namespace std;


//forward declare these guys. dont need to access atm.
class Stream;
class PropPack;

class FlashMethod
{
public:
	FlashMethod();
	virtual void PT_Flash(Stream* theStream, PropPack* thePP){};
	~FlashMethod();
protected:

	string _name;
	//Component _components[3]; //make it fixed first
	//int _ncomps;
};

