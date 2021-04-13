
// ExamDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Exam.h"
#include "ExamDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CExamDlg dialog



CExamDlg::CExamDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EXAM_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CExamDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RESULT_BTN, &CExamDlg::OnBnClickedResultBtn)
END_MESSAGE_MAP()


// CExamDlg message handlers

BOOL CExamDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CExamDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CExamDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CExamDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CExamDlg::OnBnClickedResultBtn()
{
	//int num[11], i, index;
	//CComboBox* p_combo;
	//CString str, totalStr;

	//for (i = 0; i < 5; i++) num[i] = GetDlgItemInt(IDC_EDIT1+i);
	//
	//for (i = 0; i < 6; i++) {
	//	// CComboBox는 CWnd 상속
	//	p_combo = (CComboBox *)GetDlgItem(IDC_COMBO1+i);
	//	index = p_combo->GetCurSel();

	//	// CB_ERR : 콤보 박스 선택 안되었을 때, 발생, -1
	//	if (index != CB_ERR) {
	//		// 콤보박스에서 선택된 문자열 가져오기
	//		p_combo->GetLBText(index, str);
	//		num[5 + i] = _wtoi(str);
	//	}
	//	else {
	//		num[5 + i] = 0;
	//	}
	//}

	//for (i = 0; i < 11; i++) {
	//	str.Format(L"%d ", num[i]);
	//	totalStr = totalStr + str;
	//}

	//SetDlgItemText(IDC_NUM_EDIT, totalStr);

	int num[11], i;
	CString str, totalStr;

	for (i = 0; i < 11; i++) num[i] = GetDlgItemInt(IDC_EDIT1 + i);

	for (i = 0; i < 11; i++) {
		str.Format(L"%d ", num[i]);
		totalStr += str;
	}

	SetDlgItemText(IDC_NUM_EDIT, totalStr);
}
