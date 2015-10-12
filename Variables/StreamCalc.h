#pragma once
#include "StackObject.h"
#include "PropertyCalc.h"
//#include "Stream.h"
class Stream;

class StreamCalc :
	public StackObject
{
public:
	bool Solve();
	
	void SetPropertyCalc(PropertyCalc* thePC){ _propertycalc = thePC; }
	void SetRefStream(Stream* theRS){ _refstream = theRS; }
	StreamCalc();
	~StreamCalc();
private:
	PropertyCalc* _propertycalc;
	Stream* _refstream;
};

