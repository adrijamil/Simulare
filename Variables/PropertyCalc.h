
#ifndef __PROPERTYCALC_H_INCLUDED__
#define __PROPERTYCALC_H_INCLUDED__
#include <iostream>
using namespace std;
//makethis a composite?

class Stream;
//#include "PropPack.h"
class PropPack;

class PropertyCalc
{
public:
	virtual void Calculate(Stream* thestream);
	void SetParent(PropPack* thePP);
	PropertyCalc();
	~PropertyCalc();
	void AddProperty(PropertyCalc* thechild);

protected:
	string _name;
	PropPack* _parent;
	PropertyCalc** _children;
	int _nchildren;
};

#endif
