// ===============================
// AUTHOR     :		Adri
// CREATED(d/m/yy):	2/9/15
// PURPOSE     :	This is a derived of class BaseVariable to be used for doubles. 
//					Has other properties of a variable sucha as name and isknown
//					Has variable type eg pressure temperature. 
//					Variables can be a single number(pressure) or an array(composition)
// TO BE IMPLEMENTED: 
// 1. Unit conversion. This can be handled by some user interface. 
// 2. Copy/clone function
// SPECIAL NOTES:	
// ===============================
// Change History: - put name, date and description of change
// 1. Created
//==================================

#ifndef __REALVARIABLE_H_INCLUDED__
#define __REALVARIABLE_H_INCLUDED__

#include "BaseVariable.h"

enum RealVariableType {UNITLESS,PRESSURE,TEMPERATURE,MASSFLOW,MASSENTHALPY,PHYSPROPS};//handle physprops as a separate thing. cos it can't be specified etc. it's dumb.

class RealVariable :
	//template specialisation 
	public BaseVariable <double>
{
public:
	//default constructor instantiates BaseVariable as <double>
	RealVariable();  
	
	//constructor for known single element double
	RealVariable(double thedb) :BaseVariable<double>(thedb){};
	
	//constructor using known value and it's an array
	template < size_t N >
	RealVariable(double const (&thevalue)[N]) :BaseVariable<double>(thevalue){};

	//Destructor
	~RealVariable();
private:
	RealVariableType _variable_type;  //pressure, temperature etc
	bool _is_known; // is known or not. toggle this when setting/clearing variables
	bool _is_calculated; //as in is it dependent or independent (specified or calculated)
};


#endif // !__BASEVARIABLE_H__