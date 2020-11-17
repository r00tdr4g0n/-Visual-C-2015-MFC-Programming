// CRatioDlg.cpp : implementation file
//

#include "pch.h"
#include "Exercise8_1.h"
#include "CRatioDlg.h"
#include "afxdialogex.h"
#include "Exercise8_1Dlg.h"


// CRatioDlg dialog

IMPLEMENT_DYNAMIC(CRatioDlg, CDialogEx)

CRatioDlg::CRatioDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_RATIO, pParent)
	, m_nHorizontal(0)
	, m_nVertical(0)
{

}

CRatioDlg::~CRatioDlg()
{
}

void CRatioDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_HORIZONTAL, m_nHorizontal);
	DDX_Text(pDX, IDC_EDIT_VERTICAL, m_nVertical);
	DDX_Control(pDX, IDC_SLIDER_HORIZONTAL, m_sliderHorizontal);
	DDX_Control(pDX, IDC_SLIDER_VERTICAL, m_sliderVertical);
}


BEGIN_MESSAGE_MAP(CRatioDlg, CDialogEx)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_CHECK_SAME_RATIO, &CRatioDlg::OnClickedCheckSameRatio)
END_MESSAGE_MAP()


// CRatioDlg message handlers


BOOL CRatioDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	m_nHorizontal = 50;
	m_nVertical = 50;
	m_sliderHorizontal.SetRange(0,100);
	m_sliderVertical.SetRange(0, 100);
	m_sliderHorizontal.SetPos(50); 
	m_sliderVertical.SetPos(50);

	UpdateData(false);

	((CButton*)GetDlgItem(IDC_CHECK_SAME_RATIO))->SetCheck(true);
	

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CRatioDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	CExercise81Dlg* pMainDlg = (CExercise81Dlg*)AfxGetMainWnd();

	if (!((CButton*)GetDlgItem(IDC_CHECK_SAME_RATIO))->GetCheck()) {
		m_nCurHScale = m_sliderHorizontal.GetPos();
		m_nCurVScale = m_sliderVertical.GetPos();
	}
	else {
		if (pScrollBar->GetSafeHwnd() == m_sliderHorizontal.m_hWnd) {
			m_nCurHScale = m_sliderHorizontal.GetPos();
			m_nCurVScale = m_sliderHorizontal.GetPos();
			m_sliderVertical.SetPos(m_nCurVScale);
		}
		else {
			m_nCurHScale = m_sliderVertical.GetPos();
			m_nCurVScale = m_sliderVertical.GetPos();
			m_sliderHorizontal.SetPos(m_nCurVScale);
		}
	}

	m_nHorizontal = m_nCurHScale;
	m_nVertical = m_nCurVScale;

	UpdateData(false);
	pMainDlg->UpdateDrawing();

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CRatioDlg::OnClickedCheckSameRatio()
{
	// TODO: Add your control notification handler code here
	CExercise81Dlg* pMainDlg = (CExercise81Dlg*)AfxGetMainWnd();
	
	if (((CButton*)GetDlgItem(IDC_CHECK_SAME_RATIO))->GetCheck()) {
		if (m_nCurHScale != m_nCurVScale) {
			if (m_nCurHScale > m_nCurVScale) {
				m_nVertical = m_nHorizontal;
				m_sliderVertical.SetPos(m_nVertical);
			}
			else {
				m_nHorizontal = m_nVertical;
				m_sliderHorizontal.SetPos(m_nHorizontal);
			}
		}

		UpdateData(false);

		pMainDlg->UpdateDrawing();
	}
}
