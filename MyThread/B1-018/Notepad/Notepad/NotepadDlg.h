
// NotepadDlg.h : header file
//

#pragma once

typedef struct _INFO {
	char* p_info;
	int length;
}INFO, * LPINFO;

// CNotepadDlg dialog
class CNotepadDlg : public CDialogEx
{
// Construction
public:
	CNotepadDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NOTEPAD_DIALOG };
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
	afx_msg void OnBnClickedOpenBtn();
	afx_msg void OnBnClickedSaveBtn();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

	// Add
public:
	LPINFO m_info;

public:
	void CheckBom(CString str);
	virtual BOOL DestroyWindow();
};
