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
//    Alternatively we can use a dynamic array of phases and take phase in and ouHi Adri, your access code is 6269495708t. this seems slicker but is it?

// ===============================
// Change History: - put name, date and description of change
// 1. Created
//==================================
#ifndef __STREAM_H_INCLUDED__
#define __STREAM_H_INCLUDED__

#include "Fluid.h"//actually Phase.h already declared this. just keep it its guarded anyway

#include "Phase.h"
#include "FSObject.h"

#include "PropPack.h"
//class Phase;  //this way we avoid recursion in header files.


class Stream :
	public Fluid, public FSObject
	
{
	//friend class Fluid;
public:
	Stream();
	Stream(string daname);
	RealVariable* VapourFraction(){ return _phases[0]->PhaseMoleFraction(); };



	~Stream();

	Phase* Phases(int i)
	{
		return _phases[i];
	}
	void PQFlashMe(){ _proppack->PQ_Flash(this); }
	void PTFlashMe(){ _proppack->PT_Flash(this); };
	void TQFlashMe(){ _proppack->TQ_Flash(this); }
	void SetPropertyPackage(PropPack* thePP);
	
	int NComps(){ return _proppack->NComps(); }
	bool Solve();

	void Output();

private:
	Phase* _phases[3];
	PropPack* _proppack;


	

};
#endif
