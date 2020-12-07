
// Practice8_1.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CPractice81App:
// See Practice8_1.cpp for the implementation of this class
//

class CPractice81App : public CWinApp
{
public:
	CPractice81App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CPractice81App theApp;
