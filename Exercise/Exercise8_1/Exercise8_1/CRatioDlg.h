#pragma once


// CRatioDlg dialog

class CRatioDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRatioDlg)

public:
	CRatioDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CRatioDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_RATIO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int m_nHorizontal;
	int m_nVertical;
	CSliderCtrl m_sliderHorizontal;
	CSliderCtrl m_sliderVertical;
	bool m_bSameRatio;
	int m_nCurHScale;
	int m_nCurVScale;
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnClickedCheckSameRatio();
};
