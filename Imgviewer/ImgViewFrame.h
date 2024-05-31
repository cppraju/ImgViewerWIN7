#pragma once


// CImgViewFrame frame







class CImgViewFrame : public CFrameWnd
{
	DECLARE_DYNCREATE(CImgViewFrame)
protected:
	CCaptionPanelBar m_MainDlgBar;
public:
	CImgViewFrame();           // protected constructor used by dynamic creation
	virtual ~CImgViewFrame();
	bool bFrameWindowlaunched;
protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	CSplitterWnd m_SplitWnd;

	CThumbWnd *m_pThumbWnd; 
	CImgViewWnd *m_pViewWnd;
public:

	HBRUSH hbr_BkGnd;

protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
public:
	virtual BOOL DestroyWindow();
	// //applies Alpha on the dest bitmap
	HBITMAP ApplyAlpha(HWND hWnd, HBITMAP hbmSrc, WORD wAlpha);
	CThumbWnd * GetThumbWnd(void){return(m_pThumbWnd);}
	CImgViewWnd * GetImgViewWnd(void){return(m_pViewWnd);}
protected:
	virtual void PostNcDestroy();
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};


