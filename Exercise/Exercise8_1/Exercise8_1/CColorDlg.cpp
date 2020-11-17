// CColorDlg.cpp : implementation file
//

#include "pch.h"
#include "Exercise8_1.h"
#include "CColorDlg.h"
#include "afxdialogex.h"
#include "Exercise8_1Dlg.h"


// CColorDlg dialog

IMPLEMENT_DYNAMIC(CColorDlg, CDialogEx)

CColorDlg::CColorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_COLOR, pParent)
	, m_nRed(0)
	, m_nGreen(0)
	, m_nBlue(0)
{

}

CColorDlg::~CColorDlg()
{
}

void CColorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_BLUE, m_sliderBlue);
	DDX_Control(pDX, IDC_SLIDER_GREEN, m_sliderGreen);
	DDX_Control(pDX, IDC_SLIDER_RED, m_sliderRed);
	DDX_Text(pDX, IDC_EDIT_RED, m_nRed);
	DDX_Text(pDX, IDC_EDIT_GREEN, m_nGreen);
	DDX_Text(pDX, IDC_EDIT_BLUE, m_nBlue);
}


BEGIN_MESSAGE_MAP(CColorDlg, CDialogEx)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CColorDlg message handlers


BOOL CColorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	m_colorObject = RGB(0,0,0);
	m_sliderRed.SetRange(0,255);
	m_sliderGreen.SetRange(0, 255);
	m_sliderBlue.SetRange(0, 255);
	m_sliderRed.SetPos(255);
	m_nRed = 255;
	
	UpdateData(false);
	m_colorObject = RGB(m_nRed, m_nGreen, m_nBlue);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CColorDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	CExercise81Dlg* pMainDlg = (CExercise81Dlg*)AfxGetMainWnd();

	int nRed = m_sliderRed.GetPos();
	int nGreen = m_sliderGreen.GetPos();
	int nBlue = m_sliderBlue.GetPos();

	if (pScrollBar->GetSafeHwnd() == m_sliderRed.m_hWnd) {
		m_nRed = nRed;
	}
	else if (pScrollBar->GetSafeHwnd() == m_sliderGreen.m_hWnd) {
		m_nGreen = nGreen;
	}
	else if (pScrollBar->GetSafeHwnd() == m_sliderBlue.m_hWnd) {
		m_nBlue = nBlue;
	}
	else return;

	m_colorObject = RGB(nRed, nGreen, nBlue);
	UpdateData(false);
	pMainDlg->UpdateDrawing();

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}
