/*
	common header for common includes mostly for preprocessing. 
	Using MFC to create a NON doc view arch SDI
*/
#ifndef _COMMON_H
#define _COMMON_H

#define VC_EXTRALEAN

//usually defined in targetver.h
#define WINVER 0x0501		//WinXP		


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxwin.h>
#include <afxext.h>
#include <afxcmn.h>
#include <afxcview.h>
#include <afxdisp.h>        // MFC Automation classes
//#include "atltypes.h"

#include <gdiplus.h>
using namespace Gdiplus;

#endif _COMMON_H

