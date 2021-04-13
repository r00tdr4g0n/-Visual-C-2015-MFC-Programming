
// Practice11_1.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CPractice111App:
// See Practice11_1.cpp for the implementation of this class
//

class CPractice111App : public CWinApp
{
public:
	CPractice111App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CPractice111App theApp;
