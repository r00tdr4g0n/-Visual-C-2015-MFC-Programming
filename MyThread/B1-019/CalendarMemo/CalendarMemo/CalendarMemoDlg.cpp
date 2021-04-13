
// CalendarMemoDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "CalendarMemo.h"
#include "CalendarMemoDlg.h"
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


// CCalendarMemoDlg dialog



CCalendarMemoDlg::CCalendarMemoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CALENDARMEMO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCalendarMemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MY_CALENDAR, m_my_calendar);
	DDX_Control(pDX, IDC_DATE_STATIC, m_date_static);
}

BEGIN_MESSAGE_MAP(CCalendarMemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CCalendarMemoDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CCalendarMemoDlg::OnBnClickedCancel)
	ON_NOTIFY(MCN_SELCHANGE, IDC_MY_CALENDAR, &CCalendarMemoDlg::OnMcnSelchangeMyCalendar)
	ON_BN_CLICKED(IDC_SET_BTN, &CCalendarMemoDlg::OnBnClickedSetBtn)
END_MESSAGE_MAP()


// CCalendarMemoDlg message handlers

BOOL CCalendarMemoDlg::OnInitDialog()
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
	// 세 번째 인자 지정 안하면 기본 DC를 따라간다
	m_font.CreatePointFont(120, L"굴림");
	m_my_calendar.SetFont(&m_font);
	m_date_static.SetFont(&m_font);

	OnMcnSelchangeMyCalendar(NULL, NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCalendarMemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCalendarMemoDlg::OnPaint()
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
HCURSOR CCalendarMemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCalendarMemoDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CCalendarMemoDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnCancel();

	if (IDOK == MessageBox(L"프로그램을 종료하겠습니까?", L"종료 확인", MB_OKCANCEL|MB_ICONQUESTION)) {
		DestroyWindow();
	}
}


void CCalendarMemoDlg::OnMcnSelchangeMyCalendar(NMHDR* pNMHDR, LRESULT* pResult)
{
	//LPNMSELCHANGE pSelChange = reinterpret_cast<LPNMSELCHANGE>(pNMHDR);
	
	CString str;
	wchar_t* p_week_str[7] = {L"일요일", L"월요일", L"화요일", L"수요일", L"목요일", L"금요일", L"토요일"};
	FILE* p_file;

	// 날짜 사용할때 자주 사용하는 구조체
	SYSTEMTIME cur_time;
	// 선택된 날짜 정보를 cur_time 변수에 저장
	m_my_calendar.GetCurSel(&cur_time);
	str.Format(L"%d년 %d월 %d일 %s", 
		cur_time.wYear, cur_time.wMonth, cur_time.wDay, 
		p_week_str[cur_time.wDayOfWeek]);

	SetDlgItemText(IDC_DATE_STATIC, str);
	
	str.Format(L"%04d%02d%02d.dat", cur_time.wYear, cur_time.wMonth, cur_time.wDay);
	
	if (0 == _wfopen_s(&p_file, str, L"rt, ccs=UNICODE")) {
		wchar_t temp_str[1024];
		str.Empty();

		// 유니코드 형태로 읽는 함수
		// 더 이상 읽을게 없을 경우 NULL 반환
		while (fgetws(temp_str, 1024, p_file) != NULL) {
			str += temp_str;
		}

		fclose(p_file);

		str.Replace(L"\n", L"\r\n");
		SetDlgItemText(IDC_NOTE_EDIT, str);
	}
	else {
		SetDlgItemText(IDC_NOTE_EDIT, L"");
	}

	if(pResult != NULL)	*pResult = 0;
}


void CCalendarMemoDlg::OnBnClickedSetBtn()
{
	CString str;
	SYSTEMTIME cur_time;
	FILE* p_file;
	
	m_my_calendar.GetCurSel(&cur_time);
	str.Format(L"%04d%02d%02d.dat", cur_time.wYear, cur_time.wMonth, cur_time.wDay);

	// 인코딩 직접 명시하는 방법
	if(0 == _wfopen_s(&p_file, str, L"wt, ccs=UNICODE")){
		GetDlgItemText(IDC_NOTE_EDIT, str);

		str.Replace(L"\r\n", L"\n");

		fwrite((const wchar_t*)str, (str.GetLength() + 1)*2, 1, p_file);

		fclose(p_file);
	}

}
