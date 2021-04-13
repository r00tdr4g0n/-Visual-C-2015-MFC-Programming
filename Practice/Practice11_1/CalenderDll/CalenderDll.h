// CalenderDll.h : main header file for the CalenderDll DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CCalenderDllApp
// See CalenderDll.cpp for the implementation of this class
//

class CCalenderDllApp : public CWinApp
{
public:
	CCalenderDllApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
