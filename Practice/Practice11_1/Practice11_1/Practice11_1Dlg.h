
// Practice11_1Dlg.h : header file
//

#pragma once


// CPractice111Dlg dialog
class CPractice111Dlg : public CDialogEx
{
// Construction
public:
	CPractice111Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PRACTICE11_1_DIALOG };
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
	int m_nYear;
	int m_nMonth;
	CSpinButtonCtrl m_spinYear;
	CComboBox m_cbMonth;
	afx_msg void OnSelchangeComboMonth();
	afx_msg void OnDeltaposSpinYear(NMHDR* pNMHDR, LRESULT* pResult);
};
