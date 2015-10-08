#pragma once
#include "BridgeFunction.h"


class ComponentBalance :
	public BridgeFunction
{
public:
	bool Solve();
	ComponentBalance();
	~ComponentBalance();
	bool _altsolve();

};

