
// Practice3_1View.cpp : implementation of the CPractice31View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Practice3_1.h"
#endif

#include "Practice3_1Doc.h"
#include "Practice3_1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPractice31View

IMPLEMENT_DYNCREATE(CPractice31View, CView)

BEGIN_MESSAGE_MAP(CPractice31View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CPractice31View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CPractice31View construction/destruction

CPractice31View::CPractice31View() noexcept
{
	// TODO: add construction code here

}

CPractice31View::~CPractice31View()
{
}

BOOL CPractice31View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CPractice31View drawing

void CPractice31View::OnDraw(CDC* /*pDC*/)
{
	CPractice31Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CPractice31View printing


void CPractice31View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CPractice31View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPractice31View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPractice31View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CPractice31View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPractice31View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CPractice31View diagnostics

#ifdef _DEBUG
void CPractice31View::AssertValid() const
{
	CView::AssertValid();
}

void CPractice31View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPractice31Doc* CPractice31View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPractice31Doc)));
	return (CPractice31Doc*)m_pDocument;
}
#endif //_DEBUG


// CPractice31View message handlers


int CPractice31View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	AfxMessageBox(L"윈도우가 생성되었습니다.", MB_OKCANCEL|MB_ICONINFORMATION);

	return 0;
}


void CPractice31View::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	AfxMessageBox(L"왼쪽 마우스를 더블클릭 했습니까?", MB_YESNO | MB_ICONQUESTION);

	CView::OnLButtonDblClk(nFlags, point);
}


void CPractice31View::OnDestroy()
{
	CView::OnDestroy();

	// TODO: Add your message handler code here
	AfxMessageBox(L"윈도우가 종료되었습니다.", MB_YESNO | MB_ICONWARNING);
}
