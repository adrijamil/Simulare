#pragma once
#include "StackObject.h"
#include "PropertyCalc.h"
#include "Stream.h"

class StreamCalc :
	public StackObject
{
public:
	bool Solve()
	{
		bool retval;

		_refstream->GetPropertyPackage()->RefStream()->ReadStream(_refstream);
		retval=_propertycalc->Solve();
		return retval;

	}
	void SetPropertyCalc(PropertyCalc* thePC){ _propertycalc = thePC; }
	void SetRefStream(Stream* theRS){ _refstream = theRS; }
	StreamCalc();
	~StreamCalc();
private:
	PropertyCalc* _propertycalc;
	Stream* _refstream;
};

