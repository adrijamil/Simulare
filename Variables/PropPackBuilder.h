
#ifndef __PROPPACKBUILDER_H_INCLUDED__
#define __PROPPACKBUILDER_H_INCLUDED__

#include "PropPack.h"

class PropPackBuilder
{
public:
	PropPackBuilder(){
		_current_proppack = 0;
	}

	~PropPackBuilder();
	virtual void BuidPackage()
	{
		_current_proppack = new PropPack;
	}
	virtual void SetFlashMethod(FlashTypeEnum theflashtype){ _current_proppack->SetMethod(theflashtype); }
	virtual void AddComponent(string componentname){ _current_proppack->AddComponent(componentname); }
	virtual void EditPackage(PropPack* existingpackage){ _current_proppack = existingpackage; }

	virtual PropPack* GetPackage(){
		_current_proppack->Setup();

		return _current_proppack;
		_current_proppack = 0; //does this actually get executed?
	}
private:

	PropPack* _current_proppack;

};

#endif
