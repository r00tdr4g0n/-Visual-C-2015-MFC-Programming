
// Exercise8_1.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CExercise81App:
// See Exercise8_1.cpp for the implementation of this class
//

class CExercise81App : public CWinApp
{
public:
	CExercise81App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CExercise81App theApp;
