// NotepadDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Notepad.h"
#include "NotepadDlg.h"
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


// CNotepadDlg dialog



CNotepadDlg::CNotepadDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NOTEPAD_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNotepadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CNotepadDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPEN_BTN, &CNotepadDlg::OnBnClickedOpenBtn)
	ON_BN_CLICKED(IDC_SAVE_BTN, &CNotepadDlg::OnBnClickedSaveBtn)
	ON_BN_CLICKED(IDOK, &CNotepadDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CNotepadDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CNotepadDlg message handlers

BOOL CNotepadDlg::OnInitDialog()
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
	m_info = new INFO;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CNotepadDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CNotepadDlg::OnPaint()
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
HCURSOR CNotepadDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CNotepadDlg::OnBnClickedOpenBtn()
{
	// 마지막이라는 의미는 '||'
	wchar_t name_filter[] = L"모든 파일 (*.*)|*.*|CPP 파일 (*.cpp)|*.cpp|Header 파일 (*.h)|*.h|텍스트 파일 (*.txt)|*.txt||";
	
	// 첫 번째 인자
	// true : 열기용
	// false : 저장용
	CFileDialog ins_dlg(TRUE, L"cpp", L"*.cpp", OFN_HIDEREADONLY|OFN_NOCHANGEDIR, name_filter);
	
	// 필터 조건 중 기본으로 설정하고 싶을 때 사용
	ins_dlg.m_ofn.nFilterIndex = 2;

	if (IDOK == ins_dlg.DoModal()) {
		SetDlgItemText(IDC_PATH_EDIT, ins_dlg.GetPathName());

		// CStdioFile 클래스
		// 유니코드 기반 쉽게 관리 가능
		// UTF 기반을 고려하면 복잡

		FILE* p_file = NULL;
		CString str;

		// 기존 fopen_s 함수의 문제점
		// 1. 두 번째 인자는 askii 기반
		// 2. 유니코드 지원 X
		// 해결 방법 : _wfopen_s 함수 사용하면 해결
		if (0 == _wfopen_s(&p_file, ins_dlg.GetPathName(), L"rt")) {
			char temp_str[1024];
			int length;
			wchar_t unicode_str[1024];
			
			// fgets
			// 1. 한 라인씩 읽는 함수
			// 2. 읽을 라인이 없을 경우 NULL 반환
			// 3. 인코딩 주의 (유니코드, UTF, ASCII)
			// 4. ASCII로 생각하고 리드
			while (fgets(temp_str, 1024, p_file) != NULL) {
				// CString 클래스의 '+' 연산자는 ASKII가 넘어오면 유니코드로 변환해주는 기능 존재
				// 실제 읽어들인 내용은 UTF8 인코딩이기 때문에 한글 인식 문제 발생
				
				// MultiByteToWideChar
				// 1. 인코딩 형식 변환해주는 함수
				// 2. 네 번째 인자에 변환된 내용을 저장
				// 3. 반환값은 변환한 길이
				// 4. 지금 사용 목적은 길이를 구하는 것
				length = MultiByteToWideChar(CP_UTF8, 0, temp_str, -1, NULL, 0);
				// 길이를 구한 다음 그 길이를 사용해서 unicode_str에 저장하기 위해서 다시 함수 사용
				MultiByteToWideChar(CP_UTF8, 0, temp_str, -1, unicode_str, length);
				// visual studio 2019의 기본 cpp 파일 저장 인코딩 방식은 utf-8이 아니므로
				// 임의로 utf-8로 저장 후 테스트
				str += unicode_str;
			}

			// Edit Contrl의 개행은 '\n\r'을 사용해야 한다
			str.Replace(L"\n", L"\r\n");

			CheckBom(str);
			//SetDlgItemText(IDC_NOTE_EDIT, str);
			
			fclose(p_file);
		}
	}
}


void CNotepadDlg::OnBnClickedSaveBtn()
{
	wchar_t name_filter[] = L"모든 파일 (*.*)|*.*|CPP 파일 (*.cpp)|*.cpp|Header 파일 (*.h)|*.h|텍스트 파일 (*.txt)|*.txt||";

	// 첫 번째 인자
	// true : 열기용
	// false : 저장용
	CFileDialog ins_dlg(FALSE, L"cpp", L"*.cpp", OFN_HIDEREADONLY | OFN_NOCHANGEDIR | OFN_OVERWRITEPROMPT, name_filter);

	ins_dlg.m_ofn.nFilterIndex = 2;

	if (IDOK == ins_dlg.DoModal()) {
		SetDlgItemText(IDC_PATH_EDIT, ins_dlg.GetPathName());

		FILE* p_file = NULL;
		CString str;
		int length;

		if (0 == _wfopen_s(&p_file, ins_dlg.GetPathName(), L"wt")) {
			// str은 유니코드로 저장되어 있다
			GetDlgItemText(IDC_NOTE_EDIT, str);
			// 저장할 때에는 개행 문자를 다시 원상복귀
			str.Replace(L"\r\n", L"\n");

			CheckBom(str);

			fwrite(m_info->p_info, m_info->length, 1, p_file);
			// fwrite(p, length-1, 1, p_file);
			// while문 사용하고 싶으면 '\n' 확인되면
			// fwrite 실행하는 식으로 진행

			fclose(p_file);
		}
	}
}


void CNotepadDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CNotepadDlg::OnBnClickedCancel()
{
	if (IDOK == MessageBox(L"프로그램을 종료하시겠습니까?", L"종료 확인", 
		MB_OKCANCEL | MB_ICONQUESTION)) {
		CDialogEx::OnCancel();
	}
}

void CNotepadDlg::CheckBom(CString str) 
{
	BYTE checkBom[4];
	BYTE leBom[2] = { 0xff, 0xfe };
	wchar_t* strNoBom;
	m_info->length = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);

	memcpy_s(checkBom, 4, (void*)(const wchar_t*)str, 2);

	if (0 == memcmp(checkBom, leBom, 2)) {
		strNoBom = (wchar_t*)(const wchar_t*)str + 1;
		m_info->length -= 1;
		SetDlgItemText(IDC_NOTE_EDIT, strNoBom);
	}
	else {
		strNoBom = (wchar_t*)(const wchar_t*)str;
	}

	m_info->p_info = new char[m_info->length];
	WideCharToMultiByte(CP_ACP, 0, strNoBom, -1, m_info->p_info, m_info->length, NULL, NULL);
}


BOOL CNotepadDlg::DestroyWindow()
{
	if (m_info->p_info != NULL) {
		delete m_info->p_info;
	}

	return CDialogEx::DestroyWindow();
}
