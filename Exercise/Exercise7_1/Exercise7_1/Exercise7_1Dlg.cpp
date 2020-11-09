
// Exercise7_1Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Exercise7_1.h"
#include "Exercise7_1Dlg.h"
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


// CExercise71Dlg dialog



CExercise71Dlg::CExercise71Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EXERCISE7_1_DIALOG, pParent)
	, m_strYear(_T(""))
	, m_strName(_T(""))
	, m_strGrade(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExercise71Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_CONTROL, m_treeControl);
	DDX_Control(pDX, IDC_LIST_CONTROL, m_listControl);
	DDX_Text(pDX, IDC_EDIT_YEAR, m_strYear);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_CBString(pDX, IDC_COMBO_GRADE, m_strGrade);
}

BEGIN_MESSAGE_MAP(CExercise71Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_INSERT, &CExercise71Dlg::OnClickedButtonInsert)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_CONTROL, &CExercise71Dlg::OnSelchangedTreeControl)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, &CExercise71Dlg::OnClickedButtonModify)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_CONTROL, &CExercise71Dlg::OnItemchangedListControl)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CExercise71Dlg::OnClickedButtonDelete)
	ON_NOTIFY(NM_SETFOCUS, IDC_TREE_CONTROL, &CExercise71Dlg::OnSetfocusTreeControl)
	ON_NOTIFY(NM_SETFOCUS, IDC_LIST_CONTROL, &CExercise71Dlg::OnSetfocusListControl)
END_MESSAGE_MAP()


// CExercise71Dlg message handlers

BOOL CExercise71Dlg::OnInitDialog()
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
	m_hRoot = m_treeControl.InsertItem(L"영상물", 0, TVI_LAST);
	m_hMovie = m_treeControl.InsertItem(L"영화", m_hRoot, TVI_LAST);
	m_hDrama = m_treeControl.InsertItem(L"드라마", m_hRoot, TVI_LAST);

	LPWSTR list[3] = { L"제품명",L"제작년도" ,L"등급" };
	int nWidth[3] = {100, 160, 80};

	for (int i = 0; i < 3; i++) {
		m_listControl.InsertColumn(i, list[i], LVCFMT_CENTER, nWidth[i]);
	}

	m_nCount = 0;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CExercise71Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CExercise71Dlg::OnPaint()
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
HCURSOR CExercise71Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CExercise71Dlg::OnClickedButtonInsert()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);

	CString category = (m_hSelectedNode == m_hMovie) ? L"영화" : L"드라마";

	if (m_hSelectedNode != m_hRoot) {
		for (int i = 0; i < m_nCount; i++) {
			if (m_strName == m_productInfo[i].strTitle && m_productInfo[i].strCategory == category) {
				AfxMessageBox(L"중복된 작품이 있습니다.");
				return;
			}
		}

		if (!m_strName.IsEmpty() && !m_strYear.IsEmpty() && !m_strGrade.IsEmpty()) {
			m_listControl.DeleteAllItems();

			m_productInfo[m_nCount].strCategory = category;
			m_productInfo[m_nCount].strTitle = m_strName;
			m_productInfo[m_nCount].strYear = m_strYear;
			m_productInfo[m_nCount].strGrade = m_strGrade;

			for (int i = 0,cnt=0; i <= m_nCount; i++) {
				if (m_productInfo[i].strCategory == category) {
					m_listControl.InsertItem(cnt, m_productInfo[i].strTitle);
					m_listControl.SetItem(cnt, 1, LVIF_TEXT, m_productInfo[i].strYear, 0, 0, 0, 0);
					m_listControl.SetItem(cnt, 2, LVIF_TEXT, m_productInfo[i].strGrade, 0, 0, 0, 0);
					cnt++;
				}
			}

			m_strName.Empty();
			m_strYear.Empty();
			m_strGrade.Empty();
			((CComboBox*)GetDlgItem(IDC_COMBO_GRADE))->SetCurSel(-1);

			m_nCount++;

			UpdateData(false);
		}
		else {
			AfxMessageBox(L"모든 항목을 입력해 주세요.");
		}
	}
	else {
		AfxMessageBox(L"작품 장르를 선택해 주세요");
	}
	
}


void CExercise71Dlg::OnSelchangedTreeControl(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	m_hSelectedNode = pNMTreeView->itemNew.hItem;
	m_listControl.DeleteAllItems();
	CString category = (m_hSelectedNode == m_hMovie) ? L"영화" : L"드라마";

	for (int i = 0, cnt = 0; i < m_nCount; i++) {
		if (m_productInfo[i].strCategory == category) {
			m_listControl.InsertItem(cnt,m_productInfo[i].strTitle);
			m_listControl.SetItem(cnt,1,LVIF_TEXT,m_productInfo[i].strYear,0,0,0,0);
			m_listControl.SetItem(cnt, 2, LVIF_TEXT, m_productInfo[i].strGrade, 0, 0, 0, 0);
			cnt++;
		}
	}

	*pResult = 0;
}


void CExercise71Dlg::OnClickedButtonModify()
{
	// TODO: Add your control notification handler code here
	if (!m_listControl.GetSelectedCount()) return;

	CString category = (m_hSelectedNode == m_hMovie) ? L"영화" : L"드라마";
	int select = 0;

	for (int i = 0; i < m_nCount; i++) {
		if (m_productInfo[i].strCategory == category && m_productInfo[i].strTitle == m_strName) {
			select = i;
			break;
		}
	}

	UpdateData(true);

	for (int i = 0; i < m_nCount; i++) {
		if (m_productInfo[i].strCategory == category&&m_productInfo[i].strTitle==m_strName&&i!=select) {
			AfxMessageBox(L"중복된 작품이 있습니다.");
			return;
		}
	}

	m_productInfo[select].strTitle = m_strName;
	m_productInfo[select].strYear = m_strYear;
	m_productInfo[select].strGrade = m_strGrade;

	m_listControl.SetItemText(m_nSelectedItem, 0, m_productInfo[select].strTitle);
	m_listControl.SetItemText(m_nSelectedItem, 1, m_productInfo[select].strYear);
	m_listControl.SetItemText(m_nSelectedItem, 2, m_productInfo[select].strGrade);

	m_strName.Empty();
	m_strYear.Empty();
	m_strGrade.Empty();
	((CComboBox*)GetDlgItem(IDC_COMBO_GRADE))->SetCurSel(-1);

	UpdateData(false);
}


void CExercise71Dlg::OnItemchangedListControl(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	m_nSelectedItem = pNMLV->iItem;

	if (m_listControl.GetSelectedCount()) {
		m_strName = m_listControl.GetItemText(m_nSelectedItem, 0);
		m_strYear = m_listControl.GetItemText(m_nSelectedItem, 1);
		m_strGrade = m_listControl.GetItemText(m_nSelectedItem, 2);
	}
	else {
		m_strName = "";
		m_strYear = "";
		m_strGrade = "";
		((CComboBox*)GetDlgItem(IDC_COMBO_GRADE))->SetCurSel(-1);
	}

	UpdateData(false);

	*pResult = 0;
}


void CExercise71Dlg::OnClickedButtonDelete()
{
	// TODO: Add your control notification handler code here
	if (!m_listControl.GetSelectedCount()) return;

	CString category = (m_hSelectedNode == m_hMovie) ? L"영화" : L"드라마";
	int select=0;

	m_listControl.DeleteItem(m_nSelectedItem);

	for (int i = 0; i < m_nCount; i++) {
		if (m_productInfo[i].strCategory == category && m_productInfo[i].strTitle == m_strName) {
			select = i;
			break;
		}
	}

	for (int i = select+1; i < m_nCount; i++) {
		m_productInfo[i - 1] = m_productInfo[i];
	}

	m_strName.Empty();
	m_strYear.Empty();
	m_strGrade.Empty();
	((CComboBox*)GetDlgItem(IDC_COMBO_GRADE))->SetCurSel(-1);
	m_nCount--;

	UpdateData(false);
}


void CExercise71Dlg::OnSetfocusTreeControl(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
	((CButton*)GetDlgItem(IDC_BUTTON_INSERT))->EnableWindow(true);
	((CButton*)GetDlgItem(IDC_BUTTON_MODIFY))->EnableWindow(false);
	((CButton*)GetDlgItem(IDC_BUTTON_DELETE))->EnableWindow(false);
	*pResult = 0;
}


void CExercise71Dlg::OnSetfocusListControl(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
	((CButton*)GetDlgItem(IDC_BUTTON_INSERT))->EnableWindow(false);
	((CButton*)GetDlgItem(IDC_BUTTON_MODIFY))->EnableWindow(true);
	((CButton*)GetDlgItem(IDC_BUTTON_DELETE))->EnableWindow(true);
	*pResult = 0;
}
