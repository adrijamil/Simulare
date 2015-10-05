#include "stdafx.h"
#include "fwStream.h"
#include "Stream.h"

fwStream::fwStream()
{
}

fwStream::fwStream(Stream* thestream)
{
	 Pressure=thestream->Pressure()->GetValue();
	 Temperature = thestream->Temperature()->GetValue(); 
	 X = thestream->Phases(1)->Composition()->GetValues();
	 Y = thestream->Phases(0)->Composition()->GetValues();
	 Z = thestream->Composition()->GetValues();
	 NPhases = 2;
}
fwStream::~fwStream()
{

}
