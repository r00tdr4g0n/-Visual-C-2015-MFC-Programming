
// Practice8_1Dlg.h : header file
//

#pragma once
#include "CObjectDlg.h"
#include "CColorDlg.h"

// CPractice81Dlg dialog
class CPractice81Dlg : public CDialogEx
{
// Construction
public:
	CPractice81Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PRACTICE8_1_DIALOG };
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
	int m_nSize;
	CSpinButtonCtrl m_spinSize;
	CColorDlg m_dlgColor;
	CObjectDlg m_dlgObject;
	void UpdateDrawing();
	afx_msg void OnSelchangeTabSelection(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinSize(NMHDR* pNMHDR, LRESULT* pResult);
};
