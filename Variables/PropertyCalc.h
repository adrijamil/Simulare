
#ifndef __PROPERTYCALC_H_INCLUDED__
#define __PROPERTYCALC_H_INCLUDED__
#include <iostream>
using namespace std;
//makethis a composite?


#include "fwStream.h"
//#include "PropPack.h"
#include "StackObject.h"

class PropPack;

class PropertyCalc 
{
public:
	virtual bool Solve();
	void SetParent(PropPack* thePP);
	PropertyCalc();
	~PropertyCalc();
	void AddProperty(PropertyCalc* thechild);
	PropertyCalc* GetProperty(int i){ return _children[i]; }
	int NChildren() { return _nchildren; }
	virtual RealVariable** GetVariables(Stream* refstream){	return 0;
	}
protected:
	string _name;
	PropPack* _parent;
	PropertyCalc** _children;
	int _nchildren;
};

#endif
