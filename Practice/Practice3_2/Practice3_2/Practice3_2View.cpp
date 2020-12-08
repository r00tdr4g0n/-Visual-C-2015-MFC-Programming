
// Practice3_2View.cpp : implementation of the CPractice32View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Practice3_2.h"
#endif

#include "Practice3_2Doc.h"
#include "Practice3_2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPractice32View

IMPLEMENT_DYNCREATE(CPractice32View, CView)

BEGIN_MESSAGE_MAP(CPractice32View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CPractice32View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CPractice32View construction/destruction

CPractice32View::CPractice32View() noexcept :
	m_bTimerRun(false),
	m_bTimerType(true)
{
	// TODO: add construction code here

}

CPractice32View::~CPractice32View()
{
}

BOOL CPractice32View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CPractice32View drawing

void CPractice32View::OnDraw(CDC* pDC)
{
	CPractice32Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	CRect rect;
	GetClientRect(&rect);
	pDC->DrawText(m_strTimer, rect, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
}


// CPractice32View printing


void CPractice32View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CPractice32View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPractice32View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPractice32View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CPractice32View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPractice32View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CPractice32View diagnostics

#ifdef _DEBUG
void CPractice32View::AssertValid() const
{
	CView::AssertValid();
}

void CPractice32View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPractice32Doc* CPractice32View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPractice32Doc)));
	return (CPractice32Doc*)m_pDocument;
}
#endif //_DEBUG


// CPractice32View message handlers


int CPractice32View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	SetTimer(0,1000,NULL);
	m_bTimerRun = true;

	return 0;
}


void CPractice32View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	int hour;
	CString str;
	CTime timer;
	timer = CTime::GetCurrentTime();

	if (m_bTimerType) {
		m_strTimer.Format(L"현재는 %d년 %d월 %d일 %d시 %d분 %d초입니다.",
			timer.GetYear(),
			timer.GetMonth(),
			timer.GetDay(),
			timer.GetHour(),
			timer.GetMinute(),
			timer.GetSecond());
	}
	else {
		hour = timer.GetHour();

		if (hour >= 12) {
			str = L"PM";

			if (hour >= 13) {
				hour = hour - 12;
			}
		}
		else {
			str = L"AM";
		}

		m_strTimer.Format(L"지금은 %s %d시 %d분 %d초입니다.",
			str, hour, timer.GetMinute(), timer.GetSecond());
	}

	Invalidate();

	CView::OnTimer(nIDEvent);
}


void CPractice32View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_bTimerType) {
		if (AfxMessageBox(L"시, 분, 초 형태로 표시하시겠습니까?", MB_YESNO | MB_ICONQUESTION) == IDYES) {
			m_bTimerType = false;
		}
	}
	else {
		if (AfxMessageBox(L"년, 월, 일, 시, 분, 초 형태로 표시하시겠습니까?", MB_YESNO | MB_ICONQUESTION) == IDYES) {
			m_bTimerType = true;
		}
	}

	CView::OnLButtonDown(nFlags, point);
}


void CPractice32View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_bTimerRun == false) {
		if (AfxMessageBox(L"디지털 시계를 동작시키겠습니까?", MB_YESNO|MB_ICONQUESTION) == IDYES) {
			SetTimer(0, 1000, NULL);
			m_bTimerRun = true;
		}
	}
	else {
		if (AfxMessageBox(L"정말로 디지털 시계 동작을 멈추겠습니까?", MB_YESNO | MB_ICONQUESTION) == IDYES) {
			KillTimer(0);
			m_bTimerRun = false;
		}
	}

	CView::OnRButtonDown(nFlags, point);
}
