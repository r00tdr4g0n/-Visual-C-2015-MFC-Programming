
// Practice3_1View.h : interface of the CPractice31View class
//

#pragma once


class CPractice31View : public CView
{
protected: // create from serialization only
	CPractice31View() noexcept;
	DECLARE_DYNCREATE(CPractice31View)

// Attributes
public:
	CPractice31Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CPractice31View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
};

#ifndef _DEBUG  // debug version in Practice3_1View.cpp
inline CPractice31Doc* CPractice31View::GetDocument() const
   { return reinterpret_cast<CPractice31Doc*>(m_pDocument); }
#endif

