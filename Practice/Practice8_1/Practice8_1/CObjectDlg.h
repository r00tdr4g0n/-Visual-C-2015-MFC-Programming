#pragma once


// CObjectDlg dialog

class CObjectDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CObjectDlg)

public:
	CObjectDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CObjectDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_OBJECT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int m_nSelObject;
	virtual BOOL OnInitDialog();
	afx_msg void OnRadioRect();
	afx_msg void OnRadioCircle();
};
