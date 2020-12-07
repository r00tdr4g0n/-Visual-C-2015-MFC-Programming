
// Practice8_2.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CPractice82App:
// See Practice8_2.cpp for the implementation of this class
//

class CPractice82App : public CWinApp
{
public:
	CPractice82App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CPractice82App theApp;
