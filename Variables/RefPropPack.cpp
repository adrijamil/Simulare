#include "stdafx.h"
#include "RefPropPack.h"
#include "RefPropFunctions.h" //if I put this line in the header file a linker error will happen


// Then get pointers into the dll to the actual functions.
//ABFL1dll = (fp_ABFL1dllTYPE)GetProcAddress(RefpropdllInstance, "ABFL1dll");
//ABFL2dll = (fp_ABFL2dllTYPE)GetProcAddress(RefpropdllInstance, "ABFL2dll");
//ACTVYdll = (fp_ACTVYdllTYPE)GetProcAddress(RefpropdllInstance, "ACTVYdll");
//AGdll = (fp_AGdllTYPE)GetProcAddress(RefpropdllInstance, "AGdll");
//CCRITdll = (fp_CCRITdllTYPE)GetProcAddress(RefpropdllInstance, "CCRITdll");
//CP0dll = (fp_CP0dllTYPE)GetProcAddress(RefpropdllInstance, "CP0dll");
//CRITPdll = (fp_CRITPdllTYPE)GetProcAddress(RefpropdllInstance, "CRITPdll");
//CSATKdll = (fp_CSATKdllTYPE)GetProcAddress(RefpropdllInstance, "CSATKdll");
//CV2PKdll = (fp_CV2PKdllTYPE)GetProcAddress(RefpropdllInstance, "CV2PKdll");
//CVCPKdll = (fp_CVCPKdllTYPE)GetProcAddress(RefpropdllInstance, "CVCPKdll");
//CVCPdll = (fp_CVCPdllTYPE)GetProcAddress(RefpropdllInstance, "CVCPdll");
//DBDTdll = (fp_DBDTdllTYPE)GetProcAddress(RefpropdllInstance, "DBDTdll");
//DBFL1dll = (fp_DBFL1dllTYPE)GetProcAddress(RefpropdllInstance, "DBFL1dll");
//DBFL2dll = (fp_DBFL2dllTYPE)GetProcAddress(RefpropdllInstance, "DBFL2dll");
//DDDPdll = (fp_DDDPdllTYPE)GetProcAddress(RefpropdllInstance, "DDDPdll");
//DDDTdll = (fp_DDDTdllTYPE)GetProcAddress(RefpropdllInstance, "DDDTdll");
//DEFLSHdll = (fp_DEFLSHdllTYPE)GetProcAddress(RefpropdllInstance, "DEFLSHdll");
//DHD1dll = (fp_DHD1dllTYPE)GetProcAddress(RefpropdllInstance, "DHD1dll");
//DHFLSHdll = (fp_DHFLSHdllTYPE)GetProcAddress(RefpropdllInstance, "DHFLSHdll");
//DIELECdll = (fp_DIELECdllTYPE)GetProcAddress(RefpropdllInstance, "DIELECdll");
//DOTFILLdll = (fp_DOTFILLdllTYPE)GetProcAddress(RefpropdllInstance, "DOTFILLdll");
//DPDD2dll = (fp_DPDD2dllTYPE)GetProcAddress(RefpropdllInstance, "DPDD2dll");
//DPDDKdll = (fp_DPDDKdllTYPE)GetProcAddress(RefpropdllInstance, "DPDDKdll");
//DPDDdll = (fp_DPDDdllTYPE)GetProcAddress(RefpropdllInstance, "DPDDdll");
//DPDTKdll = (fp_DPDTKdllTYPE)GetProcAddress(RefpropdllInstance, "DPDTKdll");
//DPDTdll = (fp_DPDTdllTYPE)GetProcAddress(RefpropdllInstance, "DPDTdll");
//DPTSATKdll = (fp_DPTSATKdllTYPE)GetProcAddress(RefpropdllInstance, "DPTSATKdll");
//DSFLSHdll = (fp_DSFLSHdllTYPE)GetProcAddress(RefpropdllInstance, "DSFLSHdll");
//ENTHALdll = (fp_ENTHALdllTYPE)GetProcAddress(RefpropdllInstance, "ENTHALdll");
//ENTROdll = (fp_ENTROdllTYPE)GetProcAddress(RefpropdllInstance, "ENTROdll");
//ESFLSHdll = (fp_ESFLSHdllTYPE)GetProcAddress(RefpropdllInstance, "ESFLSHdll");
//FGCTYdll = (fp_FGCTYdllTYPE)GetProcAddress(RefpropdllInstance, "FGCTYdll");
//FPVdll = (fp_FPVdllTYPE)GetProcAddress(RefpropdllInstance, "FPVdll");
//GERG04dll = (fp_GERG04dllTYPE)GetProcAddress(RefpropdllInstance, "GERG04dll");
//GETFIJdll = (fp_GETFIJdllTYPE)GetProcAddress(RefpropdllInstance, "GETFIJdll");
//GETKTVdll = (fp_GETKTVdllTYPE)GetProcAddress(RefpropdllInstance, "GETKTVdll");
//GIBBSdll = (fp_GIBBSdllTYPE)GetProcAddress(RefpropdllInstance, "GIBBSdll");
//HSFLSHdll = (fp_HSFLSHdllTYPE)GetProcAddress(RefpropdllInstance, "HSFLSHdll");
//INFOdll = (fp_INFOdllTYPE)GetProcAddress(RefpropdllInstance, "INFOdll");
//LIMITKdll = (fp_LIMITKdllTYPE)GetProcAddress(RefpropdllInstance, "LIMITKdll");
//LIMITSdll = (fp_LIMITSdllTYPE)GetProcAddress(RefpropdllInstance, "LIMITSdll");
//LIMITXdll = (fp_LIMITXdllTYPE)GetProcAddress(RefpropdllInstance, "LIMITXdll");
//MELTPdll = (fp_MELTPdllTYPE)GetProcAddress(RefpropdllInstance, "MELTPdll");
//MELTTdll = (fp_MELTTdllTYPE)GetProcAddress(RefpropdllInstance, "MELTTdll");
//MLTH2Odll = (fp_MLTH2OdllTYPE)GetProcAddress(RefpropdllInstance, "MLTH2Odll");
//NAMEdll = (fp_NAMEdllTYPE)GetProcAddress(RefpropdllInstance, "NAMEdll");
//PDFL1dll = (fp_PDFL1dllTYPE)GetProcAddress(RefpropdllInstance, "PDFL1dll");
//PDFLSHdll = (fp_PDFLSHdllTYPE)GetProcAddress(RefpropdllInstance, "PDFLSHdll");
//PEFLSHdll = (fp_PEFLSHdllTYPE)GetProcAddress(RefpropdllInstance, "PEFLSHdll");
//PHFL1dll = (fp_PHFL1dllTYPE)GetProcAddress(RefpropdllInstance, "PHFL1dll");
//PHFLSHdll = (fp_PHFLSHdllTYPE)GetProcAddress(RefpropdllInstance, "PHFLSHdll");
//PQFLSHdll = (fp_PQFLSHdllTYPE)GetProcAddress(RefpropdllInstance, "PQFLSHdll");
//PREOSdll = (fp_PREOSdllTYPE)GetProcAddress(RefpropdllInstance, "PREOSdll");
//PRESSdll = (fp_PRESSdllTYPE)GetProcAddress(RefpropdllInstance, "PRESSdll");
//PSFL1dll = (fp_PSFL1dllTYPE)GetProcAddress(RefpropdllInstance, "PSFL1dll");
//PSFLSHdll = (fp_PSFLSHdllTYPE)GetProcAddress(RefpropdllInstance, "PSFLSHdll");
//PUREFLDdll = (fp_PUREFLDdllTYPE)GetProcAddress(RefpropdllInstance, "PUREFLDdll");
//QMASSdll = (fp_QMASSdllTYPE)GetProcAddress(RefpropdllInstance, "QMASSdll");
//QMOLEdll = (fp_QMOLEdllTYPE)GetProcAddress(RefpropdllInstance, "QMOLEdll");
//SATDdll = (fp_SATDdllTYPE)GetProcAddress(RefpropdllInstance, "SATDdll");
//SATEdll = (fp_SATEdllTYPE)GetProcAddress(RefpropdllInstance, "SATEdll");
//SATHdll = (fp_SATHdllTYPE)GetProcAddress(RefpropdllInstance, "SATHdll");
//SATPdll = (fp_SATPdllTYPE)GetProcAddress(RefpropdllInstance, "SATPdll");
//SATSdll = (fp_SATSdllTYPE)GetProcAddress(RefpropdllInstance, "SATSdll");
//SATTdll = (fp_SATTdllTYPE)GetProcAddress(RefpropdllInstance, "SATTdll");
//SETAGAdll = (fp_SETAGAdllTYPE)GetProcAddress(RefpropdllInstance, "SETAGAdll");
//SETKTVdll = (fp_SETKTVdllTYPE)GetProcAddress(RefpropdllInstance, "SETKTVdll");
//SETMIXdll = (fp_SETMIXdllTYPE)GetProcAddress(RefpropdllInstance, "SETMIXdll");
//SETMODdll = (fp_SETMODdllTYPE)GetProcAddress(RefpropdllInstance, "SETMODdll");
//SETREFdll = (fp_SETREFdllTYPE)GetProcAddress(RefpropdllInstance, "SETREFdll");
//SETUPdll = (fp_SETUPdllTYPE)GetProcAddress(RefpropdllInstance, "SETUPdll");
//SPECGRdll = (fp_SPECGRdllTYPE)GetProcAddress(RefpropdllInstance, "SPECGRdll");
//SUBLPdll = (fp_SUBLPdllTYPE)GetProcAddress(RefpropdllInstance, "SUBLPdll");
//SUBLTdll = (fp_SUBLTdllTYPE)GetProcAddress(RefpropdllInstance, "SUBLTdll");
//SURFTdll = (fp_SURFTdllTYPE)GetProcAddress(RefpropdllInstance, "SURFTdll");
//SURTENdll = (fp_SURTENdllTYPE)GetProcAddress(RefpropdllInstance, "SURTENdll");
//TDFLSHdll = (fp_TDFLSHdllTYPE)GetProcAddress(RefpropdllInstance, "TDFLSHdll");
//TEFLSHdll = (fp_TEFLSHdllTYPE)GetProcAddress(RefpropdllInstance, "TEFLSHdll");
//THERM0dll = (fp_THERM0dllTYPE)GetProcAddress(RefpropdllInstance, "THERM0dll");
//THERM2dll = (fp_THERM2dllTYPE)GetProcAddress(RefpropdllInstance, "THERM2dll");
//THERM3dll = (fp_THERM3dllTYPE)GetProcAddress(RefpropdllInstance, "THERM3dll");
//THERMdll = (fp_THERMdllTYPE)GetProcAddress(RefpropdllInstance, "THERMdll");
//THFLSHdll = (fp_THFLSHdllTYPE)GetProcAddress(RefpropdllInstance, "THFLSHdll");
//TPFLSHdll = (fp_TPFLSHdllTYPE)GetProcAddress(RefpropdllInstance, "TPFLSHdll");
//TPRHOdll = (fp_TPRHOdllTYPE)GetProcAddress(RefpropdllInstance, "TPRHOdll");
//TQFLSHdll = (fp_TQFLSHdllTYPE)GetProcAddress(RefpropdllInstance, "TQFLSHdll");
//TRNPRPdll = (fp_TRNPRPdllTYPE)GetProcAddress(RefpropdllInstance, "TRNPRPdll");
//TSFLSHdll = (fp_TSFLSHdllTYPE)GetProcAddress(RefpropdllInstance, "TSFLSHdll");
//VIRBdll = (fp_VIRBdllTYPE)GetProcAddress(RefpropdllInstance, "VIRBdll");
//VIRCdll = (fp_VIRCdllTYPE)GetProcAddress(RefpropdllInstance, "VIRCdll");
//WMOLdll = (fp_WMOLdllTYPE)GetProcAddress(RefpropdllInstance, "WMOLdll");
//XMASSdll = (fp_XMASSdllTYPE)GetProcAddress(RefpropdllInstance, "XMASSdll");
//XMOLEdll = (fp_XMOLEdllTYPE)GetProcAddress(RefpropdllInstance, "XMOLEdll");


RefPropPack::RefPropPack()
{
	//define where fluids are- change to point to "C:\\Program Files (x86)\\REFPROP\\

	_fluids_path = "D:\\East101\\Adri\\devprojects\\theSeed\\RefProp\\fluids";

	//maybe lump this in a setup proc// then lump that in a proppack factory
	//load an instance of the dll
	RefProp_dll_instance = LoadLibrary("C:\\Program Files (x86)\\REFPROP\\REFPROP.DLL");

	//create a method to check if instance is still valid/setup

	//Map the function defined in RefPropFunctions.h to the function which exists in the dll

	SETUPdll = (fp_SETUPdllTYPE)GetProcAddress(RefProp_dll_instance, "SETUPdll");
	TPFLSHdll = (fp_TPFLSHdllTYPE)GetProcAddress(RefProp_dll_instance, "TPFLSHdll");


	//set it up
	long i, ierr;
	char hf[refpropcharlength*ncmax], hrf[lengthofreference + 1],
		herr[errormessagelength + 1], hfmix[refpropcharlength + 1];
	double x[ncmax];
	i = 3;
	ierr = 0;
	//strcpy_s(hf, "D:\\East101\\Adri\\devprojects\\theSeed\\RefProp\\fluids\\METHANE.FLD");
	strcpy_s(hf, "D:\\East101\\Adri\\devprojects\\theSeed\\RefProp\\fluids\\METHANE.FLD|D:\\East101\\Adri\\devprojects\\theSeed\\RefProp\\fluids\\ETHANE.FLD|D:\\East101\\Adri\\devprojects\\theSeed\\RefProp\\fluids\\BENZENE.FLD");
	/*strcpy_s(hf, "D:\\East101\\Adri\\devprojects\\theSeed\\RefProp\\fluids\\ARGON.FLD");
	strcpy_s(hf, "D:\\East101\\Adri\\devprojects\\theSeed\\RefProp\\fluids\\OXYGEN.FLD");*/
	strcpy_s(hfmix, "D:\\East101\\Adri\\devprojects\\theSeed\\RefProp\\fluids\\HMX.BNC");
	strcpy_s(hrf, "DEF");
	strcpy_s(herr, "Ok");
	
	
	//...Call SETUP to initialize the program
	SETUPdll(i, hf, hfmix, hrf, ierr, herr,
		refpropcharlength*ncmax, refpropcharlength,
		lengthofreference, errormessagelength);
	if (ierr != 0) printf("%s\n", herr);
	std::cout << hf;

}

void RefPropPack::PT_Flash(Stream* thestream)
{

	//setup arrays to be dynamic
	long i, ierr;
	char hf[refpropcharlength*ncmax], hrf[lengthofreference + 1],
		herr[errormessagelength + 1], hfmix[refpropcharlength + 1];
	double t, p, d, dl, dv, q, e, h, s, cv, cp, w;
	double x[ncmax], xliq[ncmax], xvap[ncmax], f[ncmax];

	
	//extract components and compositions

	t = thestream->Temperature()->GetValue();
	p = thestream->Pressure()->GetValue();
	
	for (int k = 0; k < _ncomps; k++)
	{
		x[k] = thestream->Composition()->GetValue(k);
	}
	//x = thestream->Composition()->GetValues();

	//setupdll - initialise the fluid
	// do PT flash
	//...Calculate pressure (p), internal energy (e), enthalpy (h), entropy (s),
	//.....isochoric (cv) and isobaric (cp) heat capacities, speed of sound (w),
	TPFLSHdll(t, p, x, d, dl, dv, xliq, xvap, q, e, h, s, cv, cp, w, ierr, herr, errormessagelength);
	//cout<< herr;

	//send back to stream
	for (int i = 0; i < _ncomps; i++)
	{
		thestream->Phases(0)->Composition()->SetValue(i, xvap[i]);
		thestream->Phases(1)->Composition()->SetValue(i, xliq[i]);
		//Yi[i] = _Ki[i] * Xi[i];
	}

	//put it into the stream

	thestream->Phases(0)->PhaseMoleFraction()->SetValue(q);
	thestream->Phases(1)->PhaseMoleFraction()->SetValue(1 - q);

}



RefPropPack::~RefPropPack()
{
}