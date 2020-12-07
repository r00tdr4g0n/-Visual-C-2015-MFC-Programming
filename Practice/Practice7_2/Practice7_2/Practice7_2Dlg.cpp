
// Practice7_2Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Practice7_2.h"
#include "Practice7_2Dlg.h"
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


// CPractice72Dlg dialog



CPractice72Dlg::CPractice72Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PRACTICE7_2_DIALOG, pParent)
	, m_strSelectedNode(_T(""))
	, m_strNodeText(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPractice72Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_CONTROL, m_treeControl);
	DDX_Text(pDX, IDC_EDIT_SELECTED_NODE, m_strSelectedNode);
	DDX_Text(pDX, IDC_EDIT_NODE_TEXT, m_strNodeText);
}

BEGIN_MESSAGE_MAP(CPractice72Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_CONTROL, &CPractice72Dlg::OnSelchangedTreeControl)
	ON_BN_CLICKED(IDC_BUTTON_INSERT, &CPractice72Dlg::OnClickedButtonInsert)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, &CPractice72Dlg::OnClickedButtonModify)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CPractice72Dlg::OnClickedButtonDelete)
	ON_BN_CLICKED(IDC_CHECK_EXPAND, &CPractice72Dlg::OnClickedCheckExpand)
END_MESSAGE_MAP()


// CPractice72Dlg message handlers

BOOL CPractice72Dlg::OnInitDialog()
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
	m_hRoot = m_treeControl.InsertItem(L"루트 노드", 0, TVI_LAST);
	((CButton*)GetDlgItem(IDC_CHECK_EXPAND))->SetCheck(true);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPractice72Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPractice72Dlg::OnPaint()
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
HCURSOR CPractice72Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPractice72Dlg::OnSelchangedTreeControl(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	m_hSelectedNode = pNMTreeView->itemNew.hItem;
	m_strSelectedNode = m_treeControl.GetItemText(m_hSelectedNode);
	UpdateData(false);
	*pResult = 0;
}


void CPractice72Dlg::OnClickedButtonInsert()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	if (!m_strNodeText.IsEmpty()) {
		m_treeControl.InsertItem(m_strNodeText, m_hSelectedNode, TVI_LAST);
		m_treeControl.Expand(m_hSelectedNode, TVE_EXPAND);
	}
	else {
		AfxMessageBox(L"입력 노드의 텍스트를 입력하세요.");
	}
	m_strNodeText.Empty();
	UpdateData(false);
}


void CPractice72Dlg::OnClickedButtonModify()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);

	if (!m_strNodeText.IsEmpty()) {
		if (m_hSelectedNode != m_hRoot) {
			m_treeControl.SetItemText(m_hSelectedNode, m_strNodeText);
			m_strSelectedNode = m_strNodeText;
		}
		else {
			AfxMessageBox(L"루트 노드는 수정해서는 안됩니다.");
		}
	}
	else {
		AfxMessageBox(L"수정 노드의 텍스트를 입력하세요.");
	}
	m_strNodeText.Empty();
	UpdateData(false);
}


void CPractice72Dlg::OnClickedButtonDelete()
{
	// TODO: Add your control notification handler code here
	if (m_hSelectedNode != m_hRoot) {
		if (MessageBox(L"정말 삭제하시겠습니까?", L"삭제 경고", MB_YESNO) == IDYES) {
			m_treeControl.DeleteItem(m_hSelectedNode);
		}
	}
	else {
		AfxMessageBox(L"루트 노드는 삭제해서는 안됩니다.");
	}
}


void CPractice72Dlg::OnClickedCheckExpand()
{
	// TODO: Add your control notification handler code here
	m_bChecked = !m_bChecked;
	m_treeControl.Expand(m_hRoot, TVE_TOGGLE);
	m_hSelectedNode = m_hRoot;
	m_strSelectedNode = L"루트 노드";
	UpdateData(false);
}
