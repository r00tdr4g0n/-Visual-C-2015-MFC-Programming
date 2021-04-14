
// TimerDlg.h : header file
//

#pragma once


// CTimerDlg dialog
class CTimerDlg : public CDialogEx
{
private:
	bool m_timer_flag = false;

// Construction
public:
	CTimerDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TIMER_DIALOG };
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
	afx_msg void OnBnClickedGettimeBtn();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedGettimeAlwaysBtn();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();

	// 강제로 SetTimer callback 사용하는 방법
	// 멤버 함수가 아니므로 멤버 변수 사용하기 어려움
	// static void CALLBACK CTimerDlg::MyTimerProc(HWND ah_wnd, UINT a_msg_id, UINT_PTR a_timer_id, DWORD a_system_time);
};
