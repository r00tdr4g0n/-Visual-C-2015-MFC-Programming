
// Practice9_1.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CPractice91App:
// See Practice9_1.cpp for the implementation of this class
//

class CPractice91App : public CWinApp
{
public:
	CPractice91App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CPractice91App theApp;
