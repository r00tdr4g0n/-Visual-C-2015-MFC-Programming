
// Practice9_1Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Practice9_1.h"
#include "Practice9_1Dlg.h"
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


// CPractice91Dlg dialog



CPractice91Dlg::CPractice91Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PRACTICE9_1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPractice91Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON_BACKGND, m_cbtnBackgnd);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON_TEXT, m_cbtnText);
	DDX_Control(pDX, IDC_MFCFONTCOMBO_TEXT, m_fcbText);
	DDX_Control(pDX, IDC_MFCPROPERTYGRID_CARD, m_pgCardInfo);
	//  DDX_Control(pDX, IDC_MFCVSLISTBOX_CARDLIST, m_listNameCard);
	DDX_Control(pDX, IDC_MFCVSLISTBOX_CARDLIST, m_listNameCard);
}

BEGIN_MESSAGE_MAP(CPractice91Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED, OnPropertyChanged)
END_MESSAGE_MAP()


// CPractice91Dlg message handlers

BOOL CPractice91Dlg::OnInitDialog()
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
	m_cbtnBackgnd.SetColor(RGB(255,255,255));
	m_cbtnText.SetColor(RGB(0,0,0));

	LOGFONT lf;
	afxGlobalData.fontRegular.GetLogFont(&lf);
	m_fcbText.SelectFont(lf.lfFaceName);

	m_listNameCard.SetWindowTextW(L"NameCard");

	//InitializePropGrid(NameCard());

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPractice91Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPractice91Dlg::OnPaint()
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
HCURSOR CPractice91Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPractice91Dlg::AddNameCard(CString strName)
{
	// TODO: Add your implementation code here.
	NameCard card;
	card.strName = strName;

	m_pNameCards[m_nCount++] = card;
	DrawNameCard(card);
	InitializePropGrid(card);
}


void CPractice91Dlg::SelectNameCard(int nIndex)
{
	// TODO: Add your implementation code here.
	m_nSelectedCard = nIndex;
	DrawNameCard(m_pNameCards[nIndex]);
	InitializePropGrid(m_pNameCards[nIndex]);
}


void CPractice91Dlg::DeleteNameCard(int nIndex)
{
	// TODO: Add your implementation code here.
	if (nIndex != (m_nCount - 1)) {
		memcpy(&m_pNameCards[nIndex], &m_pNameCards[nIndex + 1], sizeof(NameCard) * (m_nCount - nIndex + 1));
	}
	m_nCount--;
}


void CPractice91Dlg::InitializePropGrid(NameCard card)
{
	// TODO: Add your implementation code here.
	HDITEM item;
	item.cxy = 110;
	item.mask = HDI_WIDTH;
	m_pgCardInfo.GetHeaderCtrl().SetItem(0, &item);

	m_pgCardInfo.RemoveAll();
	m_pgCardInfo.EnableHeaderCtrl(false);
	m_pgCardInfo.SetVSDotNetLook();
	m_pgCardInfo.EnableDescriptionArea();

	CMFCPropertyGridProperty* pGroupInfo = new CMFCPropertyGridProperty(L"Information");
	
	pGroupInfo->AddSubItem(new CMFCPropertyGridProperty(L"Company", card.strCompany, L"회사이름을 입력하세요", 0));

	CMFCPropertyGridProperty* pTitle = new CMFCPropertyGridProperty(L"Title", card.strTitle, L"직책을 선택하세요.", 1);
	pTitle->AddOption(L"대표이사");
	pTitle->AddOption(L"부장");
	pTitle->AddOption(L"과장");
	pTitle->AddOption(L"대리");
	pTitle->AddOption(L"사원");
	pTitle->AllowEdit(false);

	pGroupInfo->AddSubItem(pTitle);
	pGroupInfo->AddSubItem(new CMFCPropertyGridProperty(L"Name", card.strName, L"이름을 입력하세요.", 2));
	pGroupInfo->AddSubItem(new CMFCPropertyGridProperty(L"Telephone", card.strTelephone, L"전화번호를 입력하세요.", 3));
	pGroupInfo->AddSubItem(new CMFCPropertyGridProperty(L"Mobile", card.strMobile, L"핸드폰 번호를 입력하세요.", 4));
	pGroupInfo->AddSubItem(new CMFCPropertyGridProperty(L"Email", card.strEmail, L"메일주소를 입력하세요.", 5));

	m_pgCardInfo.AddProperty(pGroupInfo);
	m_pgCardInfo.UpdateData(false);
}


void CPractice91Dlg::DrawNameCard(NameCard card)
{
	// TODO: Add your implementation code here.
	CRect rc;
	CFont font, * pOldFont;
	CDC* pDC = GetDlgItem(IDC_STATIC_NAMECARD)->GetDC();
	GetDlgItem(IDC_STATIC_NAMECARD)->GetClientRect(&rc);

	pDC->FillSolidRect(&rc, m_cbtnBackgnd.GetColor());
	pDC->SetBkColor(m_cbtnBackgnd.GetColor());

	LOGFONT lf;
	CMFCFontInfo* pInfo = m_fcbText.GetSelFont();
	afxGlobalData.fontRegular.GetLogFont(&lf);

	lf.lfCharSet = pInfo->m_nCharSet;
	lf.lfPitchAndFamily = pInfo->m_nPitchAndFamily;
	lstrcpyn(lf.lfFaceName, pInfo->m_strName, LF_FACESIZE);
	lf.lfHeight = 50;

	font.CreateFontIndirectW(&lf);
	pOldFont = pDC->SelectObject(&font);
	pDC->SetTextColor(m_cbtnText.GetColor());
	pDC->TextOut(15,15,card.strCompany);

	CRect rcTitle(rc);
	rcTitle.right = rc.CenterPoint().x;
	pDC->DrawText(card.strTitle, &rcTitle, DT_RIGHT|DT_VCENTER|DT_SINGLELINE);

	CRect rcName(rc);
	rcName.left = rc.CenterPoint().x;
	pDC->DrawText(card.strName, &rcName, DT_CENTER|DT_VCENTER|DT_SINGLELINE);

	pDC->SelectObject(pOldFont);
	font.DeleteObject();

	lf.lfCharSet = pInfo->m_nCharSet;
	lf.lfPitchAndFamily = pInfo->m_nPitchAndFamily;
	lstrcpyn(lf.lfFaceName, pInfo->m_strName, LF_FACESIZE);
	lf.lfHeight = 15;

	font.CreateFontIndirectW(&lf);
	pOldFont = pDC->SelectObject(&font);
	pDC->SetTextColor(m_cbtnText.GetColor());

	CString str;
	CRect rcMail(rc);

	rcMail.right = rcMail.right - 6;
	rcMail.bottom = rcMail.bottom - 6;
	str.Format(L"전자메일 : %s", card.strEmail);
	int nHeight = pDC->DrawText(str, &rcMail, DT_RIGHT|DT_BOTTOM|DT_SINGLELINE);

	str.Format(L"개인전화 : %s", card.strMobile);
	rcMail.bottom = rcMail.bottom - lf.lfHeight;
	nHeight = pDC->DrawText(str, &rcMail, DT_RIGHT|DT_BOTTOM|DT_SINGLELINE);

	str.Format(L"대표전화 : %s", card.strTelephone);
	rcMail.bottom = rcMail.bottom - lf.lfHeight;
	nHeight = pDC->DrawText(str, &rcMail, DT_RIGHT | DT_BOTTOM | DT_SINGLELINE);

	pDC->SelectObject(pOldFont);
	font.DeleteObject();
}

LRESULT CPractice91Dlg::OnPropertyChanged(WPARAM wParam, LPARAM lParam)
{
	CMFCPropertyGridProperty* pProperty = (CMFCPropertyGridProperty*)lParam;

	switch (pProperty->GetData()) {
	case 0:
		m_pNameCards[m_nSelectedCard].strCompany = pProperty->GetValue();
		break;
	case 1:
		m_pNameCards[m_nSelectedCard].strTitle = pProperty->GetValue();
		break;
	case 2:
		m_pNameCards[m_nSelectedCard].strName = pProperty->GetValue();
		break;
	case 3:
		m_pNameCards[m_nSelectedCard].strTelephone = pProperty->GetValue();
		break;
	case 4:
		m_pNameCards[m_nSelectedCard].strMobile = pProperty->GetValue();
		break;
	case 5:
		m_pNameCards[m_nSelectedCard].strEmail = pProperty->GetValue();
		break;
	}

	DrawNameCard(m_pNameCards[m_nSelectedCard]);
	return 0L;
}