
// TimerDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Timer.h"
#include "TimerDlg.h"
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


// CTimerDlg dialog



CTimerDlg::CTimerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TIMER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTimerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTimerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CTimerDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CTimerDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_GETTIME_BTN, &CTimerDlg::OnBnClickedGettimeBtn)
	ON_BN_CLICKED(IDC_GETTIME_ALWAYS_BTN, &CTimerDlg::OnBnClickedGettimeAlwaysBtn)
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CTimerDlg message handlers

BOOL CTimerDlg::OnInitDialog()
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

void CTimerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTimerDlg::OnPaint()
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
HCURSOR CTimerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTimerDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CTimerDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void CTimerDlg::OnBnClickedGettimeBtn()
{
	//// C 방법
	//// 19700101 이후 경과 시간을 초로 반환
	//time_t cur_time = time(NULL);
	//// 대한민국 기준 UTD+09:00
	//// year 은 +1900
	//// month 는 +1
	//tm p_time;
	//localtime_s(&p_time, &cur_time);
	//CString str;

	//str.Format(L"%d - %d - %d %d:%d:%d", 
	//	p_time.tm_year+1900, p_time.tm_mon+1, p_time.tm_mday, p_time.tm_hour, p_time.tm_min, p_time.tm_sec);

	//SetDlgItemText(IDC_TIME_EDIT, str);

	//// MFC 방법
	//// 밀리세컨드 단위 x
	//CString str;
	//CTime cur_time = CTime::GetCurrentTime();

	///*str.Format(L"%d-%d-%d %d:%d:%d", 
	//	cur_time.GetYear(), cur_time.GetMonth(), cur_time.GetDay(), cur_time.GetHour(), cur_time.GetMinute(), cur_time.GetSecond());*/

	//// 간단하게 형식 지정하는 방법
	//// CTime 제공 Format 함수 사용
	//str = cur_time.Format("%Y-%m-%d %H:%M:%S");

	// 밀리세컨드 단위 o
	CString str;
	SYSTEMTIME cur_time;
	
	GetLocalTime(&cur_time);
	str.Format(L"%d-%d-%d %d:%d:%d(%dms)",
			cur_time.wYear, cur_time.wMonth, cur_time.wDay, cur_time.wHour, cur_time.wMinute, cur_time.wSecond, cur_time.wMilliseconds);

	SetDlgItemText(IDC_TIME_EDIT, str);
}


BOOL CTimerDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN) {
		if (pMsg->wParam == VK_ESCAPE) {
			return true;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CALLBACK MyTimerProc(HWND ah_wnd, UINT a_msg_id, UINT_PTR a_timer_id, DWORD a_system_time)
{
	if (a_timer_id == 1) {
		// 전역함수이기 때문에 클래스 멤버에 접근 불가능
		
		// 1. 메시지 활용 
		// 버튼들은 보통 WM_COMMAND 메시지 발생시킨다
		// 버튼 정보를 세 번째 인자로 넘겨준다
		// 네 번째 인자는 버튼에 대한 윈도우 핸들이지만, 생략해도 무관
		//::SendMessage(ah_wnd, WM_COMMAND, MAKEWPARAM(IDC_GETTIME_BTN, BN_CLICKED), 0);

		// 강제로 윈도우 핸들 가져오기
		static_cast<CTimerDlg*>(::AfxGetApp()->m_pMainWnd)->OnBnClickedGettimeBtn();
	}
}

void CTimerDlg::OnBnClickedGettimeAlwaysBtn()
{
	// TODO: Add your control notification handler code here
	// timer 생성
	// WM_TIMER 메시지 발생
	// flag성 메시지
	// 중복 생성, 제거 문제 없음
	if (!m_timer_flag) {
		//SetTimer(1, 200, NULL);

		// Callback
		SetTimer(1, 200, MyTimerProc);
		m_timer_flag = !m_timer_flag;
	}
}

void CTimerDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 1) {
		OnBnClickedGettimeBtn();
	}
	else {
		CDialogEx::OnTimer(nIDEvent);
	}
}


void CTimerDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here

	if (m_timer_flag) {
		KillTimer(1);
	}
}
