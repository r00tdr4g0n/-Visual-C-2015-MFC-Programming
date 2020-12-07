
// Exercise2_2View.cpp : implementation of the CExercise22View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Exercise2_2.h"
#endif

#include "Exercise2_2Doc.h"
#include "Exercise2_2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExercise22View

IMPLEMENT_DYNCREATE(CExercise22View, CView)

BEGIN_MESSAGE_MAP(CExercise22View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CExercise22View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SIZE()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CExercise22View construction/destruction

CExercise22View::CExercise22View() noexcept:m_bDrag(false)
{
	// TODO: add construction code here

}

CExercise22View::~CExercise22View()
{
}

BOOL CExercise22View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CExercise22View drawing

void CExercise22View::OnDraw(CDC* pDC)
{
	CExercise22Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	CRect rect;
	GetClientRect(&rect);
	m_strPointText.Format(L"X:%d Y:%d", m_ptMouseMove.x, m_ptMouseMove.y);

	pDC->TextOutW(10, 10, m_strWindowSize);
	pDC->TextOut(m_ptMouseMove.x, m_ptMouseMove.y, m_strPointText);
	pDC->DrawText(m_strOutput, &rect, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
}


// CExercise22View printing


void CExercise22View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CExercise22View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CExercise22View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CExercise22View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CExercise22View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CExercise22View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	//theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CExercise22View diagnostics

#ifdef _DEBUG
void CExercise22View::AssertValid() const
{
	CView::AssertValid();
}

void CExercise22View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CExercise22Doc* CExercise22View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CExercise22Doc)));
	return (CExercise22Doc*)m_pDocument;
}
#endif //_DEBUG


// CExercise22View message handlers


void CExercise22View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	m_strOutput = L"키보드를 눌렀습니다.";
	Invalidate();

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CExercise22View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_bDrag = true;
	m_strOutput = L"왼쪽 마우스를 눌렀습니다.";
	Invalidate();

	CView::OnLButtonDown(nFlags, point);
}


void CExercise22View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_bDrag = false;

	CView::OnLButtonUp(nFlags, point);
}


void CExercise22View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_ptMouseMove.x = point.x;
	m_ptMouseMove.y = point.y;

	if (m_bDrag) {
		m_strOutput = L"마우스를 드래그하고 있습니다.";
	}
	else {
		m_strOutput = L"마우스를 이동 중 입니다.";
	}

	Invalidate();

	CView::OnMouseMove(nFlags, point);
}


void CExercise22View::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	m_strWindowSize.Format(L"윈도우 크기는 넓이 %d, 높이 %d입니다.", cx, cy);

	Invalidate();

	// TODO: Add your message handler code here
}


void CExercise22View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_strOutput = L"오른쪽 마우스를 눌렀습니다.";
	Invalidate();

	CView::OnRButtonDown(nFlags, point);
}
