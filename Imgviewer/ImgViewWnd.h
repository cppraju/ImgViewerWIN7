#pragma once


// CImgViewWnd


#ifndef _IMGVIEWWND_
#define _IMGVIEWWND_


class CImgViewWnd : public CWnd
{
	DECLARE_DYNCREATE(CImgViewWnd)

public:
	CImgViewWnd();
	virtual ~CImgViewWnd();
private:
	HBRUSH hb;
	WNDCLASS wc;
	HBITMAP hbmAlpha;
	HBITMAP PrepareAlphaBitmap(void);
	HCURSOR hCursorMove, hCursor;
	HBITMAP hbmbk;
public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
};


#endif