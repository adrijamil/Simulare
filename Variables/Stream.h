// ===============================
// AUTHOR     :		Adri
// CREATED(d/m/yy):	2/9/15
// PURPOSE     :	This a derived class of fluid.
//					Also Streams will have members of phases 
//					Should not need a name as it will not exist alone (or at all as a fluid object except in the implementation of subclasses)
//					Normalise method is included for testing. May not actually
//					On creation certain variables such as temperature and pressure will be pointing to the same block of memory (memory here refers to the double, not RealVariable object)
//					
// TO BE IMPLEMENTED: 
// 1. Copy/clone function
// 2. Attach a thermo package
// 3. Deal with phases that are not there

// SPECIAL NOTES:	
// 1. Static initialisation of Phases to 3 phases. Phases then need to know whether they exist or not. \
//    Alternatively we can use a dynamic array of phases and take phase in and out. this seems slicker but is it?

// ===============================
// Change History: - put name, date and description of change
// 1. Created
//==================================
#ifndef __STREAM_H_INCLUDED__
#define __STREAM_H_INCLUDED__

#include "Fluid.h"
#include "Phase.h"



#include "PropPack.h"
//class Phase;  //this way we avoid recursion in header files.


class Stream :
	public Fluid
	
{
	//friend class Fluid;
public:
	Stream();
	
	~Stream();
	Phase* Phases(int i)
	{
		return _phases[i];
	}

	void PTFlashMe(){ _proppack->PT_Flash(this); };
	void SetPropertyPackage(PropPack* thePP);
	
	string Name() { return _name; }

private:
	Phase* _phases[3];
	PropPack* _proppack;
	string _name;

};
#endif
