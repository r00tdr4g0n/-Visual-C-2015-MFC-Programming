
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

// 색상 직접 지정
void MyVGradientFill(CDC *ap_dc, CRect *ap_rect, COLORREF a_start_color, COLORREF a_end_color)
{
	TRIVERTEX data[2];
	GRADIENT_RECT r;

	data[0].x = ap_rect->left; // left
	data[0].y = ap_rect->top; // top

	// rgb 일일이 지정
	// 16bit 색상 지원하므로 (<<8) 해준다
	data[0].Red = 0;
	data[0].Green = 128 << 8;
	data[0].Blue = 255 << 8;
	data[0].Alpha = 0; // 투명도

	data[1].x = ap_rect->right; // rigth
	data[1].y = ap_rect->bottom; // bottom

	data[1].Red = 0;
	data[1].Green = 255 << 8;
	data[1].Blue = 255 << 8;
	data[1].Alpha = 0; // 투명도

	r.UpperLeft = 0;
	r.LowerRight = 1;

	ap_dc->GradientFill(data, 2, &r, 1, GRADIENT_FILL_RECT_V);
}

// 인자로 받은 색상 사용
void MyHGradientFill(CDC* ap_dc, CRect* ap_rect, COLORREF a_start_color, COLORREF a_end_color)
{
	TRIVERTEX data[2];
	GRADIENT_RECT r;

	data[0].x = ap_rect->left; // left
	data[0].y = ap_rect->top; // top

	// rgb 일일이 지정
	// 16bit 색상 지원하므로 (<<8) 해준다
	data[0].Red = GetRValue(a_start_color) << 8;
	data[0].Green = GetGValue(a_start_color) << 8;
	data[0].Blue = GetBValue(a_start_color) << 8;
	data[0].Alpha = 0; // 투명도

	data[1].x = ap_rect->right; // rigth
	data[1].y = ap_rect->bottom; // bottom

	data[1].Red = GetRValue(a_end_color) << 8;
	data[1].Green = GetGValue(a_end_color) << 8;
	data[1].Blue = GetBValue(a_end_color) << 8;
	data[1].Alpha = 0; // 투명도

	r.UpperLeft = 0;
	r.LowerRight = 1;

	ap_dc->GradientFill(data, 2, &r, 1, GRADIENT_FILL_RECT_H);
}

// a_is_vertical 변수 하나로 V, H 구분해서 함수 개수 줄이기
void MyGradientFill(CDC* ap_dc, CRect* ap_rect, COLORREF a_start_color, COLORREF a_end_color, 
	int a_is_vertical = 1)
{
	TRIVERTEX data[2];
	GRADIENT_RECT r;

	data[0].x = ap_rect->left; // left
	data[0].y = ap_rect->top; // top

	// rgb 일일이 지정
	// 16bit 색상 지원하므로 (<<8) 해준다
	data[0].Red = GetRValue(a_start_color) << 8;
	data[0].Green = GetGValue(a_start_color) << 8;
	data[0].Blue = GetBValue(a_start_color) << 8;
	data[0].Alpha = 0; // 투명도

	data[1].x = ap_rect->right; // rigth
	data[1].y = ap_rect->bottom; // bottom

	data[1].Red = GetRValue(a_end_color) << 8;
	data[1].Green = GetGValue(a_end_color) << 8;
	data[1].Blue = GetBValue(a_end_color) << 8;
	data[1].Alpha = 0; // 투명도

	r.UpperLeft = 0;
	r.LowerRight = 1;

	// 마지막 인자
	// 0 : Horizontal
	// 1 : Vertical
	ap_dc->GradientFill(data, 2, &r, 1, a_is_vertical);
}

// 입체적 그라데이션
// 절반씩 나눠서 그라데이션
void My3DGradientFill(CDC* ap_dc, CRect* ap_rect, COLORREF a_start_color, COLORREF a_end_color)
{
	TRIVERTEX data[2];
	GRADIENT_RECT r;

	data[0].x = ap_rect->left; // left
	data[0].y = ap_rect->top; // top

	// rgb 일일이 지정
	// 16bit 색상 지원하므로 (<<8) 해준다
	data[0].Red = GetRValue(a_start_color) << 8;
	data[0].Green = GetGValue(a_start_color) << 8;
	data[0].Blue = GetBValue(a_start_color) << 8;
	data[0].Alpha = 0; // 투명도

	data[1].x = ap_rect->right; // rigth
	data[1].y = ap_rect->top + (ap_rect->bottom - ap_rect->top)/2; // bottom

	data[1].Red = GetRValue(a_end_color) << 8;
	data[1].Green = GetGValue(a_end_color) << 8;
	data[1].Blue = GetBValue(a_end_color) << 8;
	data[1].Alpha = 0; // 투명도

	r.UpperLeft = 0;
	r.LowerRight = 1;

	ap_dc->GradientFill(data, 2, &r, 1, GRADIENT_FILL_RECT_V);

	// 중간부터 끝까지 그리기
	// 색상은 반대로 적용
	data[0].x = ap_rect->left; // left
	data[0].y = ap_rect->top + (ap_rect->bottom - ap_rect->top) / 2;

	data[0].Red = GetRValue(a_end_color) << 8;
	data[0].Green = GetGValue(a_end_color) << 8;
	data[0].Blue = GetBValue(a_end_color) << 8;
	data[0].Alpha = 0; // 투명도

	data[1].x = ap_rect->right; // left
	data[1].y = ap_rect->bottom;

	data[1].Red = GetRValue(a_start_color) << 8;
	data[1].Green = GetGValue(a_start_color) << 8;
	data[1].Blue = GetBValue(a_start_color) << 8;
	data[1].Alpha = 0; // 투명도

	ap_dc->GradientFill(data, 2, &r, 1, GRADIENT_FILL_RECT_V);
}

void CExamDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	if (IsIconic())
	{

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
		// 그라데이션 실습

		My3DGradientFill(&dc, &CRect(10, 10, 210, 100), RGB(0, 128, 255), RGB(0, 255, 255));
		MyGradientFill(&dc, &CRect(220, 10, 420, 100), RGB(0, 128, 255), RGB(0, 255, 255));
		My3DGradientFill(&dc, &CRect(430, 10, 630, 100), RGB(0, 255, 255), RGB(0, 128, 255));

		//CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CExamDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

