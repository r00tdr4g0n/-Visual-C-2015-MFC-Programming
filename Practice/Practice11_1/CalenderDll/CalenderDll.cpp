// CalenderDll.cpp : Defines the initialization routines for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "CalenderDll.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: If this DLL is dynamically linked against the MFC DLLs,
//		any functions exported from this DLL which call into
//		MFC must have the AFX_MANAGE_STATE macro added at the
//		very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

// CCalenderDllApp

BEGIN_MESSAGE_MAP(CCalenderDllApp, CWinApp)
END_MESSAGE_MAP()


// CCalenderDllApp construction

CCalenderDllApp::CCalenderDllApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CCalenderDllApp object

CCalenderDllApp theApp;


// CCalenderDllApp initialization

BOOL CCalenderDllApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

// 외부에서 호출할 함수
extern "C" __declspec(dllexport) void Calender(int year, int month, int *days);

// Calender 함수에서 사용할 함수들로서 미리 선언
int FirstDay(int year, int month);
bool IsLeapYear(int year);


// 윤년 구분하여 각 달에 대한 날짜 수
static int DaysOfMonth[2][12] =
{
	{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

// 시작 년도와 마지막 년도
int m_nStartYear = 1583;
int m_nEndYear = 4040;
int m_nStartMonth = 0;

// 윤년 판별 함수 
bool IsLeapYear(int year)
{
	if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) {
		return true;
	}
	else {
		return false;
	}
}

int FirstDay(int year, int month)
{
	int i, day = 0;

	for (i = m_nStartYear; i < year; i++) {
		if (IsLeapYear(i)) {
			day += 366;
		}
		else {
			day += 365;
		}
		day %= 7;
	}

	for (i = m_nStartMonth; i < month; i++) {
		day += DaysOfMonth[IsLeapYear(year)][i];
		day %= 7;
	}

	if (day == 0) {
		day = 7;
	}

	return (day - 1);
}

__declspec(dllexport) void Calender(int year, int month, int *days)
{
	int thisDay, endDay, week, i;

	thisDay = FirstDay(year, month);
	endDay = DaysOfMonth[IsLeapYear(year)][month];
	week = 0;

	for (i = 1; i <= endDay; i++) {
		*(days + (week * 7) + thisDay) = i;
		thisDay++;

		if (thisDay == 7) {
			thisDay = 0;
			week++;
		}
	}
}