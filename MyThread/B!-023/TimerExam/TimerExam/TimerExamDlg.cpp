
// TimerExamDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "TimerExam.h"
#include "TimerExamDlg.h"
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


// CTimerExamDlg dialog



CTimerExamDlg::CTimerExamDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TIMEREXAM_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTimerExamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTimerExamDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CTimerExamDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CTimerExamDlg::OnBnClickedCancel)
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CTimerExamDlg message handlers

BOOL CTimerExamDlg::OnInitDialog()
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
	
	// Ŭ���̾�Ʈ ������ ���� ���� ���ϱ�
	CRect r;
	GetClientRect(r);

	int w = r.Width(), h = r.Height();

	// ���� �õ� �ð�����
	srand((unsigned int)time(NULL));

	for (int i = 0; i < MAX_COUNT; i++) {
		// ���� �õ尡 �ð��̱� ������ ������ �ұ�Ģ
		m_list[i].x = rand() % w;	// 0~(w-1)
		m_list[i].y = rand() % h;	// 0~(h-1)
		// �ּ� ������ 10, �ִ� 49
		m_list[i].r = rand() % 40 + 10;
		m_list[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);
	}

	SetTimer(1, 100, NULL);	// WM_TIMER

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTimerExamDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTimerExamDlg::OnPaint()
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
		CircleData* p = m_list;
		// for �� �ȿ��� dc �Ҵ� ������ ��� �ݺ����� �ʴ� ���
		// GetCurrentBrush �Լ��� ���� dc�� �̸� ���� ��
		// for �� ����� ���Ҵ�
		CBrush fill_brush, *p_old_brush = dc.GetCurrentBrush();;

		for (int i = 0; i < MAX_COUNT; i++) {
			fill_brush.CreateSolidBrush(p->color);
			
			dc.SelectObject(&fill_brush);
			dc.Ellipse(p->x - p->r, p->y - p->r, p->x + p->r, p->y + p->r);
			p++;
			
			fill_brush.DeleteObject();
		}

		dc.SelectObject(p_old_brush);

		// CPaintDC ��ü �ı��ڿ� ������ ����� �����ϹǷ�
		// �ߺ� ��ƾ ������ ���ؼ� �ּ� ó��
		//CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTimerExamDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTimerExamDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CTimerExamDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


BOOL CTimerExamDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN) {
		if (pMsg->wParam == VK_ESCAPE) {
			return true;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CTimerExamDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 1) {
		CRect r;
		GetClientRect(r);
		int w = r.Width(), h = r.Height();
		CircleData* p = m_list;

		for (int i = 0; i < MAX_COUNT; i++) {
			p->r--;

			// �������� 0�� �Ǹ� ���� �ٸ� ��ġ�� �ٽ� �׸���
			if (p->r == 0) {
				p->x = rand() % w;	// 0~(w-1)
				p->y = rand() % h;	// 0~(h-1)
				// �ּ� ������ 10, �ִ� 49
				p->r = rand() % 40 + 1;
				p->color = RGB(rand() % 256, rand() % 256, rand() % 256);
			}
			
			p++;
		}

		// Ŭ���̾�Ʈ ������ ��ȿȭ
		// ������ ��ȿȭ�� �ƴϱ� ������ �ٽ� ��ȿȭ
		// WM_PAINT �޽��� �߻�
		Invalidate();
	}
	else {
		CDialogEx::OnTimer(nIDEvent);
	}
}


void CTimerExamDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	KillTimer(1);
}
