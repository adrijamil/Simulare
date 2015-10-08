#include "stdafx.h"
#include "IsentropicCompression.h"
#include "UnitOp.h"
#include "Stream.h"

IsentropicCompression::IsentropicCompression()
{

}

IsentropicCompression::~IsentropicCompression()
{

}

bool IsentropicCompression::Solve()
{
	double F = -32767;
	enum CalcModeEnum { CANNOTSOLVE, FKP1, FKP2, FP1P2, KP1P2, SOLVED }; // need to know if solved or not
	CalcModeEnum CalcMode = CANNOTSOLVE;
	bool pressuresolved = false;
	RealVariable* P1 = _parent->GetStream(0, INLET)->Pressure();
	RealVariable* P2 = _parent->GetStream(0, OUTLET)->Pressure();
	RealVariable* F1 = _parent->GetStream(0, INLET)->MolarFlow();
	RealVariable* F2 = _parent->GetStream(0, OUTLET)->MolarFlow();
	//check flow
	if (_solved)
	{
		return true;
	}

	Stream* tempstream = new Stream;
	fwStream* tempfw = new fwStream;

	if (F1->IsKnown() && F2->IsCalculated())
	{
		F = F1->GetValue();
	}
	else if (F2->IsKnown() && F1->IsCalculated())
	{
		F = F2->GetValue();
	}

	if (P1->IsKnown() && P2->IsKnown())
	{
		double Q;
		double n;
		double h1;
		double h2_;
		tempfw->ReadStream(_parent->GetStream(0, INLET));
		tempfw->Phases[0].Entropy = _parent->GetStream(0, INLET)->MolarEntropy()->GetValue();
		tempfw->Pressure = P2->GetValue();
		//get h1 first
		h1 = tempfw->Phases[0].Enthalpy;
		n = _isentropicefficiency->GetValue();
			//"delete" enthalpy, temperature and vfrac
		tempfw->VapourFraction = -32767;
		tempfw->Phases[0].Enthalpy = -32767;
		tempfw->Temperature = -32767;

		tempfw->WriteStream(tempstream);
		tempstream->SetPropertyPackage(_parent->GetStream(0, INLET)->GetPropertyPackage());
		tempstream->Solve();
		
		h2_ = h1 + (tempstream->MolarEnthalpy()->GetValue() - h1) / n;
		Q = (h2_-h1)*F;
		
		_energyinput->SetValue(Q);
		_deltapressure->SetValue(P2->GetValue() - P1->GetValue());

		_parent->GetStream(0, OUTLET)->MolarEnthalpy()->SetValue(h2_);
		pressuresolved = true;

	}

	if (pressuresolved)
	{
		_solved = true;
	}

	return pressuresolved;
}
