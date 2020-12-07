
// Practice7_2.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CPractice72App:
// See Practice7_2.cpp for the implementation of this class
//

class CPractice72App : public CWinApp
{
public:
	CPractice72App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CPractice72App theApp;
