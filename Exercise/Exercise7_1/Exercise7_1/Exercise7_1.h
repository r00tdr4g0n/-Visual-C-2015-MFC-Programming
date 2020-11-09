
// Exercise7_1.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CExercise71App:
// See Exercise7_1.cpp for the implementation of this class
//

class CExercise71App : public CWinApp
{
public:
	CExercise71App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CExercise71App theApp;
