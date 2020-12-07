
// Practice2_2View.cpp : implementation of the CPractice22View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Practice2_2.h"
#endif

#include "Practice2_2Doc.h"
#include "Practice2_2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPractice22View

IMPLEMENT_DYNCREATE(CPractice22View, CView)

BEGIN_MESSAGE_MAP(CPractice22View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CPractice22View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CPractice22View construction/destruction

CPractice22View::CPractice22View() noexcept :m_bDrag(false)
{
	// TODO: add construction code here

}

CPractice22View::~CPractice22View()
{
}

BOOL CPractice22View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CPractice22View drawing

void CPractice22View::OnDraw(CDC* pDC)
{
	CPractice22Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	CRect rect;

	GetClientRect(&rect);
	pDC->TextOutW(10, 10, m_strWindowSize);
	pDC->DrawText(m_strOutput, rect, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
}


// CPractice22View printing


void CPractice22View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CPractice22View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPractice22View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPractice22View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CPractice22View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPractice22View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	//theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CPractice22View diagnostics

#ifdef _DEBUG
void CPractice22View::AssertValid() const
{
	CView::AssertValid();
}

void CPractice22View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPractice22Doc* CPractice22View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPractice22Doc)));
	return (CPractice22Doc*)m_pDocument;
}
#endif //_DEBUG


// CPractice22View message handlers


void CPractice22View::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	m_strWindowSize.Format(L"윈도우 크기는 넓이 %d, 높이 %d입니다.", cx, cy);
	Invalidate();
}


void CPractice22View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_bDrag = true;
	m_strOutput = L"왼쪽 마우스 버튼을 눌렀습니다.";
	Invalidate();

	CView::OnLButtonDown(nFlags, point);
}


void CPractice22View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_strOutput = L"오른쪽 마우스 버튼을 눌렀습니다.";
	Invalidate();

	CView::OnRButtonDown(nFlags, point);
}


void CPractice22View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	m_strOutput = L"키보드를 눌렀습니다.";
	Invalidate();

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CPractice22View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_bDrag) {
		m_strOutput = L"마우스를 드래그하고 있습니다.";
	}
	else {
		m_strOutput = L"마우스를 이동 중 입니다.";
	}

	Invalidate();

	CView::OnMouseMove(nFlags, point);
}


void CPractice22View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_bDrag = false;

	CView::OnLButtonUp(nFlags, point);
}
