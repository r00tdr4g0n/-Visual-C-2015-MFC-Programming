
// Exercise3_1View.cpp : implementation of the CExercise31View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Exercise3_1.h"
#endif

#include "Exercise3_1Doc.h"
#include "Exercise3_1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExercise31View

IMPLEMENT_DYNCREATE(CExercise31View, CView)

BEGIN_MESSAGE_MAP(CExercise31View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CExercise31View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CExercise31View construction/destruction

CExercise31View::CExercise31View() noexcept :
	m_strStopWatch(L"00:00.00"),
	m_nMinute(0),
	m_nSecond(0),
	m_nMSec(0),
	m_bStopWatchRun(false),
	m_nCount(0)
{
	// TODO: add construction code here

}

CExercise31View::~CExercise31View()
{
}

BOOL CExercise31View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CExercise31View drawing

void CExercise31View::OnDraw(CDC* pDC)
{
	CExercise31Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	CClientDC mainDC(this);
	CClientDC recordDC(this);
	CFont bigFont, smallFont, *oldFont;
	CRect rect;

	bigFont.CreateFont(100,0,0,0,
		FW_BOLD,
		false,false,0,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH|FF_SWISS, 
		L"휴먼둥근헤드라인");
	
	smallFont.CreateFont(30, 0, 0, 0,
		FW_BOLD,
		false, false, 0,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS,
		L"휴먼둥근헤드라인");
	
	GetClientRect(&rect);

	oldFont = (CFont*)(mainDC.SelectObject(&bigFont));
	recordDC.SelectObject(&smallFont);

	mainDC.DrawText(m_strStopWatch, rect, DT_SINGLELINE|DT_CENTER|DT_VCENTER);

	for (int i = 0; i < MAX; i++) {
		recordDC.TextOutW(10,10 + i * 40,m_strRecord[i]);
	}

	mainDC.SelectObject(oldFont);
	recordDC.SelectObject(oldFont);

	bigFont.DeleteObject();
	smallFont.DeleteObject();
}


// CExercise31View printing


void CExercise31View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CExercise31View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CExercise31View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CExercise31View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CExercise31View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CExercise31View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	//theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CExercise31View diagnostics

#ifdef _DEBUG
void CExercise31View::AssertValid() const
{
	CView::AssertValid();
}

void CExercise31View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CExercise31Doc* CExercise31View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CExercise31Doc)));
	return (CExercise31Doc*)m_pDocument;
}
#endif //_DEBUG


// CExercise31View message handlers


void CExercise31View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	m_nMSec++;
	
	if (m_nMSec == 100) {
		m_nMSec = 0;
		m_nSecond++;

		if (m_nSecond == 60) {
			m_nSecond = 0;
			m_nMinute++;
		}
	}

	m_strStopWatch.Format(L"%02d:%02d.%02d", m_nMinute, m_nSecond, m_nMSec);

	Invalidate();

	CView::OnTimer(nIDEvent);
}


void CExercise31View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (!m_bStopWatchRun) {
		m_bStopWatchRun = true;
		SetTimer(0,10,NULL);
	}
	else {
		m_bStopWatchRun = false;
		KillTimer(0);
	}

	CView::OnLButtonDown(nFlags, point);
}


void CExercise31View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	if (m_bStopWatchRun && nChar == VK_SPACE) {
		CString strRecord;
		strRecord.Format(L"%2d. ", m_nCount+1);
		m_strRecord[m_nCount++] = strRecord + m_strStopWatch;
		
		if (m_nCount == MAX) m_nCount = 0;
	}

	Invalidate();

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CExercise31View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (!m_bStopWatchRun) {
		if (AfxMessageBox(L"초기화 하시겠습니까?", MB_YESNO|MB_ICONQUESTION)==IDYES) {
			for (int i = 0; i < MAX;i++) {
				m_strRecord[i].Empty();
			}

			m_nCount = 0;
			m_nMinute = 0;
			m_nSecond = 0;
			m_nMSec = 0;
			m_strStopWatch = L"00:00.00";
			
		}

		Invalidate();
	}

	CView::OnRButtonDown(nFlags, point);
}
