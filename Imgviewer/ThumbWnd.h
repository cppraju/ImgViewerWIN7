#pragma once


// CThumbWnd


#ifndef _THUMBWND_
#define _THUMBWND_


class CThumbWnd : public CListCtrl
{
	DECLARE_DYNCREATE(CThumbWnd)

public:
	CThumbWnd();
	virtual ~CThumbWnd();
private:
	WNDCLASS wc;
public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	void UpdateCurrentFolder(const TCHAR *ptchCurrentDir); 
	HCURSOR hCursor;
	CBrush br;
	CBitmap bm;
	CBitmap bmCompat;
	HCURSOR hCurGrip;
	CImageList m_ImgLst;
	CImageList m_IcoLst;
	TCHAR tchPath[256];
	CList<CString, CString> lstImgFile;
	bool LoadThumbNailsFromFolder(void);
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
//	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLvnInsertitem(NMHDR *pNMHDR, LRESULT *pResult);
};


#endif