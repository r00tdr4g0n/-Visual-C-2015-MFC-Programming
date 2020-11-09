
// Exercise7_1Dlg.h : header file
//

#pragma once

typedef struct Product {
	CString strCategory;
	CString strTitle;
	CString strYear;
	CString strGrade;
}Product;

// CExercise71Dlg dialog
class CExercise71Dlg : public CDialogEx
{
// Construction
public:
	CExercise71Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EXERCISE7_1_DIALOG };
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
	Product m_productInfo[50];
	CTreeCtrl m_treeControl;
	CString m_strYear;
	CString m_strName;
	CString m_strGrade;
	HTREEITEM m_hRoot;
	HTREEITEM m_hMovie;
	HTREEITEM m_hDrama;
	int m_nCount;
	int m_nSelectedItem;
	HTREEITEM m_hSelectedNode;
	CListCtrl m_listControl;
	afx_msg void OnClickedButtonInsert();
	afx_msg void OnSelchangedTreeControl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickedButtonModify();
	afx_msg void OnItemchangedListControl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickedButtonDelete();
	afx_msg void OnSetfocusTreeControl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSetfocusListControl(NMHDR* pNMHDR, LRESULT* pResult);
};
