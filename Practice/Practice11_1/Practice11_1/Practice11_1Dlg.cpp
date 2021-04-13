
// Practice11_1Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Practice11_1.h"
#include "Practice11_1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern "C" __declspec(dllimport) void Calender(int year, int month, int *days);

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


// CPractice111Dlg dialog



CPractice111Dlg::CPractice111Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PRACTICE11_1_DIALOG, pParent)
	, m_nYear(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPractice111Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_YEAR, m_nYear);
	DDX_Control(pDX, IDC_SPIN_YEAR, m_spinYear);
	DDX_Control(pDX, IDC_COMBO_MONTH, m_cbMonth);
}

BEGIN_MESSAGE_MAP(CPractice111Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO_MONTH, &CPractice111Dlg::OnSelchangeComboMonth)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_YEAR, &CPractice111Dlg::OnDeltaposSpinYear)
END_MESSAGE_MAP()


// CPractice111Dlg message handlers

BOOL CPractice111Dlg::OnInitDialog()
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
	CTime time = CTime::GetCurrentTime();
	m_nYear = time.GetYear();
	m_nMonth = time.GetMonth() - 1;

	m_cbMonth.SetCurSel(m_nMonth);
	m_spinYear.SetRange(1583,4040);
	m_spinYear.SetPos(m_nYear);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPractice111Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPractice111Dlg::OnPaint()
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
		int m_nDays[6][7] = {0,};
		int i, j, x, y;

		x = 30;
		y = 105;

		CString m_sWeekDays[7] = {L"Sun",L"Mon" ,L"Tue" ,L"Wed" ,L"Thu" ,L"Fri" ,L"Sat" };
		CString m_sNumber;

		CPaintDC dc(this);
		dc.SetBkColor(RGB(240, 240, 240));

		for (i = 0; i < 7; i++) {
			dc.TextOutW(x,y,m_sWeekDays[i]);
			x += 50;
		}

		Calender(m_nYear, m_nMonth, &m_nDays[0][0]);

		for (i = 0; i < 6; i++) {
			x = 30;

			for (j = 0; j < 7; j++) {
				if (m_nDays[i][j] != 0) {
					m_sNumber.Format(L"%d", m_nDays[i][j]);
					dc.TextOutW(x, y+20, m_sNumber);
				}

				x += 50;
			}

			y += 20;
		}

		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPractice111Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPractice111Dlg::OnSelchangeComboMonth()
{
	// TODO: Add your control notification handler code here
	int nItem = m_cbMonth.GetCurSel();
	m_nMonth = nItem;
	Invalidate();
}


void CPractice111Dlg::OnDeltaposSpinYear(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	m_nYear += pNMUpDown->iDelta;

	if (m_nYear <= 1583) {
		m_nYear = 1583;
	}
	if (m_nYear > 4040) {
		m_nYear = 4040;
	}

	Invalidate();

	*pResult = 0;
}
