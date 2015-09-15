
#ifndef __PROPPACKBUILDER_H_INCLUDED__
#define __PROPPACKBUILDER_H_INCLUDED__

#include "PropPack.h"
#include "MolWtCalc.h"

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
	virtual void SetFlashMethod(FlashTypeEnum theflashtype)
	{
		_current_proppack->SetMethod(theflashtype);
		
		//refprop still neeeds this
		MolWtCalc* newcalc = new MolWtCalc;
		_current_proppack->AddProperty(newcalc);
		
	}
	virtual void AddComponent(string componentname){ _current_proppack->AddComponent(componentname); }
	virtual void AddPropertyCalc(string theproperty);
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
