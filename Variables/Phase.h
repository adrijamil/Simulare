// ===============================
// AUTHOR     :		Adri
// CREATED(d/m/yy):	2/9/15
// PURPOSE     :	This a derived class of fluid.
//					Also phases will be members of streams
//					Name should be something like Stream("asda").VapourPhase
//					Normalise method is included for testing.
//					On creation, certain variables owned by phase and stream such as temperature and pressure will be pointing to the same block of memory 
// (memory here refers to the double, not RealVariable object)
//					
// TO BE IMPLEMENTED: 
// 1. Copy/clone function
// 2. Attach a thermo package
// 3. Deal with phases that are not there

// SPECIAL NOTES:	
// 1. Using the structure of fixed number of phases, the phases need to then know if it is actually there or not. Maybe can put phase frac = -32767. Or put a null pointer.

// ===============================
// Change History: - put name, date and description of change
// 1. Created
//==================================

#ifndef __PHASE_H_INCLUDED__
#define __PHASE_H_INCLUDED__

#include "Fluid.h"
//#include "Stream.h"

//class Stream;  //this way we avoid recursion in header files.

enum  PhaseType { OVERALL = -1, VAPOUR,HCLIQUID, AQUEOUS, UNDEFINED };

class Phase :
	public Fluid
{
public:
	Phase()
	{ 
		_pressure = new RealVariable; 
	};

	Phase(PhaseType thetype){ 
		_phase_type = thetype; 
		_phase_mol_fraction = new RealVariable;
	};

	RealVariable* PhaseMoleFraction(){ return _phase_mol_fraction; }

	~Phase();
	void SetParent(Fluid* parentstrm);
private:
	PhaseType _phase_type = UNDEFINED;
	Fluid* _parent_stream;
	RealVariable* _phase_mol_fraction;
};

#endif