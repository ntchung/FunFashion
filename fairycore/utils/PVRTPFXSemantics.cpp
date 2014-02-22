/******************************************************************************

 @File         OGLES2/PVRTPFXSemantics.cpp

 @Title        PFX Semantics

 @Version      

 @Copyright    Copyright (c) Imagination Technologies Limited.

 @Platform     All

 @Description  A list of supported PFX semantics.

******************************************************************************/

/*****************************************************************************
** Includes
******************************************************************************/
#include "stdafx.h"

/*!***************************************************************************
** Default Shaman semantics
*****************************************************************************/
const SPVRTPFXUniformSemantic c_psSemanticsInfo[] =
{
	{ "POSITION",				ePVRTPFX_UsPOSITION					, true },
	{ "NORMAL",					ePVRTPFX_UsNORMAL					, true },
	{ "TANGENT",				ePVRTPFX_UsTANGENT 					, true },		
	{ "BINORMAL",				ePVRTPFX_UsBINORMAL 				, true },
	{ "UV",						ePVRTPFX_UsUV						, true },
	{ "VERTEXCOLOR",			ePVRTPFX_UsVERTEXCOLOR				, true },
	{ "BONEINDEX",				ePVRTPFX_UsBONEINDEX				, true },
	{ "BONEWEIGHT",				ePVRTPFX_UsBONEWEIGHT				, true },
	
	{ "WORLD",					ePVRTPFX_UsWORLD					, false },
	{ "WORLDI",					ePVRTPFX_UsWORLDI 					, false },
	{ "WORLDIT",				ePVRTPFX_UsWORLDIT					, false },
	{ "VIEW",					ePVRTPFX_UsVIEW 					, false },
	{ "VIEWI",					ePVRTPFX_UsVIEWI 					, false },
	{ "VIEWIT",					ePVRTPFX_UsVIEWIT					, false },
	{ "PROJECTION",				ePVRTPFX_UsPROJECTION				, false },
	{ "PROJECTIONI",			ePVRTPFX_UsPROJECTIONI				, false },
	{ "PROJECTIONIT",			ePVRTPFX_UsPROJECTIONIT				, false },
	{ "WORLDVIEW",				ePVRTPFX_UsWORLDVIEW				, false },
	{ "WORLDVIEWI",				ePVRTPFX_UsWORLDVIEWI				, false },
	{ "WORLDVIEWIT",			ePVRTPFX_UsWORLDVIEWIT				, false },
	{ "WORLDVIEWPROJECTION",	ePVRTPFX_UsWORLDVIEWPROJECTION		, false },
	{ "WORLDVIEWPROJECTIONI",	ePVRTPFX_UsWORLDVIEWPROJECTIONI		, false },
	{ "WORLDVIEWPROJECTIONIT",	ePVRTPFX_UsWORLDVIEWPROJECTIONIT	, false },
	{ "UNPACKMATRIX",			ePVRTPFX_UsUNPACKMATRIX				, false },

	{ "VIEWPROJECTION",			ePVRTPFX_UsVIEWPROJECTION			, false },
	{ "VIEWPROJECTIONI",		ePVRTPFX_UsVIEWPROJECTIONI			, false },
	{ "VIEWPROJECTIONIT",		ePVRTPFX_UsVIEWPROJECTIONIT			, false },
	{ "OBJECT",					ePVRTPFX_UsOBJECT					, false },
	{ "OBJECTI",				ePVRTPFX_UsOBJECTI					, false },
	{ "OBJECTIT",				ePVRTPFX_UsOBJECTIT					, false },

	{ "MATERIALOPACITY",		ePVRTPFX_UsMATERIALOPACITY			, false },
	{ "MATERIALSHININESS",		ePVRTPFX_UsMATERIALSHININESS		, false },
	{ "MATERIALCOLORAMBIENT",	ePVRTPFX_UsMATERIALCOLORAMBIENT		, false },
	{ "MATERIALCOLORDIFFUSE",	ePVRTPFX_UsMATERIALCOLORDIFFUSE 	, false },
	{ "MATERIALCOLORSPECULAR",	ePVRTPFX_UsMATERIALCOLORSPECULAR	, false },

	{ "BONECOUNT",				ePVRTPFX_UsBONECOUNT				, false },
	{ "BONEMATRIXARRAY",		ePVRTPFX_UsBONEMATRIXARRAY			, false },
	{ "BONEMATRIXARRAYIT",		ePVRTPFX_UsBONEMATRIXARRAYIT		, false },

	{ "LIGHTCOLOR",				ePVRTPFX_UsLIGHTCOLOR				, false },
	{ "LIGHTPOSMODEL",			ePVRTPFX_UsLIGHTPOSMODEL 			, false },
	{ "LIGHTPOSWORLD",			ePVRTPFX_UsLIGHTPOSWORLD			, false },
	{ "LIGHTPOSEYE",			ePVRTPFX_UsLIGHTPOSEYE				, false },
	{ "LIGHTDIRMODEL",			ePVRTPFX_UsLIGHTDIRMODEL			, false },
	{ "LIGHTDIRWORLD",			ePVRTPFX_UsLIGHTDIRWORLD			, false },
	{ "LIGHTDIREYE",			ePVRTPFX_UsLIGHTDIREYE				, false },
	{ "LIGHTATTENUATION",		ePVRTPFX_UsLIGHTATTENUATION			, false },
	{ "LIGHTFALLOFF",			ePVRTPFX_UsLIGHTFALLOFF				, false },

	{ "EYEPOSMODEL",			ePVRTPFX_UsEYEPOSMODEL				, false },
	{ "EYEPOSWORLD",			ePVRTPFX_UsEYEPOSWORLD				, false },
	{ "TEXTURE",				ePVRTPFX_UsTEXTURE					, false },
	{ "ANIMATION",				ePVRTPFX_UsANIMATION				, false },
	
	{ "VIEWPORTPIXELSIZE",		ePVRTPFX_UsVIEWPORTPIXELSIZE		, false },
	{ "VIEWPORTCLIPPING",		ePVRTPFX_UsVIEWPORTCLIPPING			, false },
	{ "TIME",					ePVRTPFX_UsTIME						, false },
	{ "TIMECOS",				ePVRTPFX_UsTIMECOS					, false },
	{ "TIMESIN",				ePVRTPFX_UsTIMESIN					, false },
	{ "TIMETAN",				ePVRTPFX_UsTIMETAN					, false },
	{ "TIME2PI",				ePVRTPFX_UsTIME2PI					, false },
	{ "TIME2PICOS",				ePVRTPFX_UsTIME2PICOS				, false },
	{ "TIME2PISIN",				ePVRTPFX_UsTIME2PISIN				, false },
	{ "TIME2PITAN",				ePVRTPFX_UsTIME2PITAN				, false },
	{ "RANDOM",					ePVRTPFX_UsRANDOM					, false },
};

const SPVRTPFXUniformSemantic* PVRTPFXSemanticsGetSemanticList()
{
	return c_psSemanticsInfo;
}

/*****************************************************************************
 End of file (PVRTPFXSemantics.cpp)
*****************************************************************************/

