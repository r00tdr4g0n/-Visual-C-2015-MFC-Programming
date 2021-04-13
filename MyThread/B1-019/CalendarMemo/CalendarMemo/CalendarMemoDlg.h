
// CalendarMemoDlg.h : header file
//

#pragma once


// CCalendarMemoDlg dialog
class CCalendarMemoDlg : public CDialogEx
{
private:
	CFont m_font;

// Construction
public:
	CCalendarMemoDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CALENDARMEMO_DIALOG };
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
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

	CMonthCalCtrl m_my_calendar;
	afx_msg void OnMcnSelchangeMyCalendar(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedSetBtn();
	CStatic m_date_static;
};
