// ===============================
// AUTHOR     :		Adri
// CREATED(d/m/yy):	7/9/15
// PURPOSE     :	This is a baseclass for FlashMethods (referring to Ideal/RefProp/PengRob
//					used to apply strategy pattern to the PropPack class
//					PropPack class keeps a reference to this object to do flash calcs
// ===============================
// TO BE IMPLEMENTED: 
// 1. To keep relevant pure component data (Tc, Pc) on board so don't have too keep reaching into PropPack 
// ===============================
// SPECIAL NOTES:	
// 1. 
// ===============================
// Change History: - put name, date and description of change
// 1. Created
//==================================


#ifndef __FLASHMETHOD_H_INCLUDED__
#define __FLASHMETHOD_H_INCLUDED__
using namespace std;

//forward declare these guys. dont need to access. for now.
class Stream;
class PropPack;

class FlashMethod
{
public:
	FlashMethod();
	virtual void PT_Flash(Stream* theStream, PropPack* thePP){};
	virtual void Setup(PropPack* thePP){};
	virtual ~FlashMethod();
protected:

	string _name; 
};

#endif