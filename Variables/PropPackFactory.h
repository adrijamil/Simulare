#pragma once

#include "PropPack.h"


class PropPackFactory
{
public:
	PropPackFactory();
	~PropPackFactory();
	PropPack* CreatePackage();

};

