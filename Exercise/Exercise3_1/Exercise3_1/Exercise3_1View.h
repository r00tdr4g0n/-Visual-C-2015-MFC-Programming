
// Exercise3_1View.h : interface of the CExercise31View class
//

#pragma once
#define MAX 10

class CExercise31View : public CView
{
protected: // create from serialization only
	CExercise31View() noexcept;
	DECLARE_DYNCREATE(CExercise31View)

// Attributes
public:
	CExercise31Doc* GetDocument() const;

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
	virtual ~CExercise31View();
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
	CString m_strStopWatch;
	CString m_strRecord[MAX];
	int m_nCount;
	int m_nMinute;
	int m_nSecond;
	int m_nMSec;
	bool m_bStopWatchRun;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in Exercise3_1View.cpp
inline CExercise31Doc* CExercise31View::GetDocument() const
   { return reinterpret_cast<CExercise31Doc*>(m_pDocument); }
#endif

