
// Exercise8_1Dlg.h : header file
//

#pragma once
#include "CObjectDlg.h"
#include "CColorDlg.h"
#include "CRatioDlg.h"


// CExercise81Dlg dialog
class CExercise81Dlg : public CDialogEx
{
// Construction
public:
	CExercise81Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EXERCISE8_1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_tabSelection;
	int m_nWSize;
	int m_nHSize;
	CSpinButtonCtrl m_spinSize;
	CObjectDlg m_dlgObject;
	CColorDlg m_dlgColor;
	CRatioDlg m_dlgRatio;
	void UpdateDrawing();
	afx_msg void OnSelchangeTabSelection(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinSize(NMHDR* pNMHDR, LRESULT* pResult);
};
