
// Practice7_2Dlg.h : header file
//

#pragma once


// CPractice72Dlg dialog
class CPractice72Dlg : public CDialogEx
{
// Construction
public:
	CPractice72Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PRACTICE7_2_DIALOG };
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
	CTreeCtrl m_treeControl;
	CString m_strSelectedNode;
	CString m_strNodeText;
	HTREEITEM m_hRoot;
	HTREEITEM m_hSelectedNode;
	bool m_bChecked;
	afx_msg void OnSelchangedTreeControl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickedButtonInsert();
	afx_msg void OnClickedButtonModify();
	afx_msg void OnClickedButtonDelete();
	afx_msg void OnClickedCheckExpand();
};
