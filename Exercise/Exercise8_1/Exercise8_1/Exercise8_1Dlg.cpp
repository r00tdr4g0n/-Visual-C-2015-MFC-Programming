
// Exercise8_1Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Exercise8_1.h"
#include "Exercise8_1Dlg.h"
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


// CExercise81Dlg dialog



CExercise81Dlg::CExercise81Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EXERCISE8_1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExercise81Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_SELECTION, m_tabSelection);
}

BEGIN_MESSAGE_MAP(CExercise81Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_SELECTION, &CExercise81Dlg::OnSelchangeTabSelection)
END_MESSAGE_MAP()


// CExercise81Dlg message handlers

BOOL CExercise81Dlg::OnInitDialog()
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
	m_nWSize = 50;
	m_nHSize = 50;

	m_tabSelection.DeleteAllItems();
	m_tabSelection.InsertItem(0, L"비율 지정");
	m_tabSelection.InsertItem(1, L"도형 선택");
	m_tabSelection.InsertItem(2, L"색상 선택");

	CRect rect;

	m_dlgRatio.Create(IDD_DIALOG_RATIO, &m_tabSelection);
	m_dlgRatio.GetWindowRect(&rect);
	m_dlgRatio.MoveWindow(5, 25, rect.Width(), rect.Height());
	m_dlgRatio.ShowWindow(SW_SHOW);

	m_dlgObject.Create(IDD_DIALOG_OBJECT, &m_tabSelection);
	m_dlgObject.GetWindowRect(&rect);
	m_dlgObject.MoveWindow(5, 30, rect.Width(), rect.Height());
	m_dlgObject.ShowWindow(SW_HIDE);

	m_dlgColor.Create(IDD_DIALOG_COLOR, &m_tabSelection);
	m_dlgColor.GetWindowRect(&rect);
	m_dlgColor.MoveWindow(5, 40, rect.Width(), rect.Height());
	m_dlgColor.ShowWindow(SW_HIDE);

	UpdateData(false);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CExercise81Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CExercise81Dlg::OnPaint()
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

	CRect rectView, rectFigure;
	GetDlgItem(IDC_STATIC_VIEW)->GetWindowRect(&rectView);
	CPoint ptCenter = rectView.CenterPoint();
	ScreenToClient(&ptCenter);
	m_nWSize = m_dlgRatio.m_nHorizontal;
	m_nHSize = m_dlgRatio.m_nVertical;

	rectFigure.left = ptCenter.x - (int)(rectView.Width() / 2.0f * (float)m_nWSize / 100.0f);
	rectFigure.right = ptCenter.x + (int)(rectView.Width() / 2.0f * (float)m_nWSize / 100.0f);
	rectFigure.top = ptCenter.y - (int)(rectView.Height() / 2.0f * (float)m_nHSize / 100.0f);
	rectFigure.bottom = ptCenter.y + (int)(rectView.Height() / 2.0f * (float)m_nHSize / 100.0f);

	CClientDC dc(this);
	CBrush newBrush, * oldBrush;

	newBrush.CreateSolidBrush(m_dlgColor.m_colorObject);
	oldBrush = dc.SelectObject(&newBrush);

	switch (m_dlgObject.m_nSelObject) {
	case 1:
		dc.Rectangle(&rectFigure);
		break;
	case 2:
		dc.Ellipse(&rectFigure);
		break;
	}

	dc.SelectObject(oldBrush);
	newBrush.DeleteObject();
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CExercise81Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CExercise81Dlg::UpdateDrawing()
{
	// TODO: Add your implementation code here.
	CRect rectView;
	GetDlgItem(IDC_STATIC_VIEW)->GetWindowRect(&rectView);
	ScreenToClient(&rectView);
	rectView.DeflateRect(1,1,1,1);

	InvalidateRect(&rectView);
}


void CExercise81Dlg::OnSelchangeTabSelection(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
	int nSelection = m_tabSelection.GetCurSel();

	switch (nSelection) {
	case 0:
		m_dlgRatio.ShowWindow(SW_SHOW);
		m_dlgObject.ShowWindow(SW_HIDE);
		m_dlgColor.ShowWindow(SW_HIDE);
		break;
	case 1:
		m_dlgRatio.ShowWindow(SW_HIDE);
		m_dlgObject.ShowWindow(SW_SHOW);
		m_dlgColor.ShowWindow(SW_HIDE);
		break;
	case 2:
		m_dlgRatio.ShowWindow(SW_HIDE);
		m_dlgObject.ShowWindow(SW_HIDE);
		m_dlgColor.ShowWindow(SW_SHOW);
		break;
	}
	*pResult = 0;
}
