
// Practice3_3View.cpp : implementation of the CPractice33View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Practice3_3.h"
#endif

#include "Practice3_3Doc.h"
#include "Practice3_3View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPractice33View

IMPLEMENT_DYNCREATE(CPractice33View, CView)

BEGIN_MESSAGE_MAP(CPractice33View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CPractice33View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CPractice33View construction/destruction

CPractice33View::CPractice33View() noexcept
	: m_strOutput(L"")
	, m_ptLocation(0)
{
	// TODO: add construction code here

}

CPractice33View::~CPractice33View()
{
}

BOOL CPractice33View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CPractice33View drawing

void CPractice33View::OnDraw(CDC* pDC)
{
	CPractice33Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	pDC->TextOutW(m_ptLocation.x, m_ptLocation.y, m_strOutput);
}


// CPractice33View printing


void CPractice33View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CPractice33View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPractice33View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPractice33View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CPractice33View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPractice33View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CPractice33View diagnostics

#ifdef _DEBUG
void CPractice33View::AssertValid() const
{
	CView::AssertValid();
}

void CPractice33View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPractice33Doc* CPractice33View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPractice33Doc)));
	return (CPractice33Doc*)m_pDocument;
}
#endif //_DEBUG


// CPractice33View message handlers


void CPractice33View::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	int nCharIndex;
	nCharIndex = m_strOutput.GetLength();

	if (nChar == VK_BACK) {
		m_strOutput.Delete(nCharIndex-1, 1);
	}
	else {
		m_strOutput += (WCHAR)nChar;
	}

	Invalidate();

	CView::OnChar(nChar, nRepCnt, nFlags);
}


void CPractice33View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	switch (nChar) {
	case VK_LEFT:
		m_ptLocation.x--;
		break;
	case VK_RIGHT:
		m_ptLocation.x++;
		break;
	case VK_UP:
		m_ptLocation.y--;
		break;
	case VK_DOWN:
		m_ptLocation.y++;
		break;
	case VK_PRIOR:
		m_ptLocation.y -= 50;
		break;
	case VK_NEXT:
		m_ptLocation.y += 50;
		break;
	case VK_HOME:
		m_ptLocation = CPoint(0);
		break;
	}

	if (m_ptLocation.x < 0) {
		m_ptLocation.x = 0;
		AfxMessageBox(L"왼쪽으로 더 이상 이동할 수 없습니다.");
	}
	if (m_ptLocation.x > m_ptClientSize.x) {
		m_ptLocation.x = m_ptClientSize.x;
		AfxMessageBox(L"오른쪽으로 더 이상 이동할 수 없습니다.");
	}
	if (m_ptLocation.y < 0) {
		m_ptLocation.y = 0;
		AfxMessageBox(L"위쪽으로 더 이상 이동할 수 없습니다.");
	}
	if (m_ptLocation.y > m_ptClientSize.y) {
		m_ptLocation.y = m_ptClientSize.y;
		AfxMessageBox(L"아래쪽으로 더 이상 이동할 수 없습니다.");
	}

	Invalidate();

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CPractice33View::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	m_ptClientSize.x = cx;
	m_ptClientSize.y = cy;

	Invalidate();
}


void CPractice33View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_ptLocation.x = point.x;
	m_ptLocation.y = point.y;

	Invalidate();

	CView::OnLButtonDown(nFlags, point);
}


void CPractice33View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_strOutput.IsEmpty() == false) {
		if (AfxMessageBox(L"문자를 모두 지우시겠습니까?", MB_YESNO | MB_ICONQUESTION) == IDYES) {
			m_strOutput.Empty();
			m_ptLocation = CPoint(0);
		}
	}
	else {
		AfxMessageBox(L"문자열을 입력하세요.");
	}

	Invalidate();

	CView::OnRButtonDown(nFlags, point);
}
