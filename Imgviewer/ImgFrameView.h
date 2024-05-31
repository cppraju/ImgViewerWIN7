#pragma once


// CImgFrameView

class CImgFrameView : public CView
{
	DECLARE_DYNCREATE(CImgFrameView)

public:
	CImgFrameView();
	virtual ~CImgFrameView();

protected:
	DECLARE_MESSAGE_MAP()
	virtual void OnDraw(CDC* /*pDC*/);
};


