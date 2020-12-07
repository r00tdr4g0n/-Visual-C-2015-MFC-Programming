
// Practice9_1Dlg.h : header file
//

#pragma once
#include "CNcardListBox.h"

typedef struct NameCard {
	CString strCompany;
	CString strTitle;
	CString strName;
	CString strTelephone;
	CString strMobile;
	CString strEmail;
}NameCard;

// CPractice91Dlg dialog
class CPractice91Dlg : public CDialogEx
{
// Construction
public:
	CPractice91Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PRACTICE9_1_DIALOG };
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
	NameCard m_pNameCards[20];
	int m_nCount;
	int m_nSelectedCard;
	void AddNameCard(CString strName);
	void SelectNameCard(int nIndex);
	void DeleteNameCard(int nIndex);
	CMFCColorButton m_cbtnBackgnd;
	CMFCColorButton m_cbtnText;
	CMFCFontComboBox m_fcbText;
	CMFCPropertyGridCtrl m_pgCardInfo;
//	CVSListBox m_listNameCard;
	CNcardListBox m_listNameCard;
	void InitializePropGrid(NameCard card);
	void DrawNameCard(NameCard card);
	afx_msg LRESULT OnPropertyChanged(WPARAM wParam, LPARAM lParam);
};
