// CObjectDlg.cpp : implementation file
//

#include "pch.h"
#include "Exercise8_1.h"
#include "CObjectDlg.h"
#include "afxdialogex.h"
#include "Exercise8_1Dlg.h"


// CObjectDlg dialog

IMPLEMENT_DYNAMIC(CObjectDlg, CDialogEx)

CObjectDlg::CObjectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_OBJECT, pParent)
{

}

CObjectDlg::~CObjectDlg()
{
}

void CObjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CObjectDlg, CDialogEx)
	ON_COMMAND(IDC_RADIO_RECT, &CObjectDlg::OnRadioRect)
	ON_COMMAND(IDC_RADIO_CIRCLE, &CObjectDlg::OnRadioCircle)
END_MESSAGE_MAP()


// CObjectDlg message handlers


BOOL CObjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	m_nSelObject = 2;
	((CButton*)GetDlgItem(IDC_RADIO_CIRCLE))->SetCheck(true);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CObjectDlg::OnRadioRect()
{
	// TODO: Add your command handler code here
	CExercise81Dlg* pMainDlg = (CExercise81Dlg *)AfxGetMainWnd();

	m_nSelObject = 1;
	pMainDlg->UpdateDrawing();
}


void CObjectDlg::OnRadioCircle()
{
	// TODO: Add your command handler code here
	CExercise81Dlg* pMainDlg = (CExercise81Dlg*)AfxGetMainWnd();

	m_nSelObject = 2;
	pMainDlg->UpdateDrawing();
}
