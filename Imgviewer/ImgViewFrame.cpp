// ImgViewFrame.cpp : implementation file
//

#include "common.h"
#include "resource.h"
#include "CaptionPanelBar.h"
#include "ImgViewer.h"



#include "ImgViewWnd.h"
#include "ThumbWnd.h"




#include "ImgViewFrame.h"

// CImgViewFrame
extern CImgWinApp theApp;



IMPLEMENT_DYNCREATE(CImgViewFrame, CFrameWnd)

CImgViewFrame::CImgViewFrame()
{
	m_pThumbWnd = NULL;
	m_pViewWnd = NULL;
	bFrameWindowlaunched = false;
}

CImgViewFrame::~CImgViewFrame()
{
}


BEGIN_MESSAGE_MAP(CImgViewFrame, CFrameWnd)
	ON_WM_CREATE()
//	ON_COMMAND(IDC_BUTTON_DIR, OnMainDlgBarDir)
//	ON_COMMAND(IDC_BUTTON_ALGO1, OnLTAlgo)
ON_WM_NCHITTEST()
ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CImgViewFrame message handlers


BOOL CImgViewFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Add your specialized code here and/or call the base class

	return CFrameWnd::PreCreateWindow(cs);
}


int CImgViewFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	//lpCreateStruct->style = lpCreateStruct->style ^ (WS_BORDER | WS_CAPTION);
	//lpCreateStruct->lpszClass = _T("ModifiedFrame");
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	//load the bitmap
	HBITMAP hbm = ::LoadBitmap(theApp.m_hInstance, MAKEINTRESOURCE(IDB_BITMAP_BKBRUSH));
	hbr_BkGnd = ::CreatePatternBrush(hbm);
	::SetClassLong(m_hWnd, GCL_HBRBACKGROUND, (LONG)hbr_BkGnd);

	m_MainDlgBar.Create(this, IDD_DIALOGBAR_MAIN, CBRS_TOP|CBRS_BOTTOM|CBRS_TOOLTIPS|CBRS_FLYBY, IDD_DIALOGBAR_MAIN);
	m_MainDlgBar.EnableDocking(CBRS_ALIGN_BOTTOM);
	//get a BKBRUSH for the dlgbar
	//HBITMAP hbmdlg = ::LoadBitmap(theApp.m_hInstance, MAKEINTRESOURCE(IDB_BITMAP_PALLET));
	//HBRUSH hbr = ::CreatePatternBrush(hbmdlg);

	//get the dimension of the dialogbar to clip the frame at the back of the dialogbar 


#ifdef _DEBUG
	{
		TCHAR xxx[128];
		_stprintf_s(xxx, sizeof(xxx)/sizeof(TCHAR), _T("CImgViewFrame::OnCreate() ===========>>>"));
		OutputDebugString(xxx);
	}
#endif
	return 0;
}

BOOL CImgViewFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: Add your specialized code here and/or call the base class
	CRect rec;
	GetClientRect(&rec);
#ifdef _DEBUG
	{
		TCHAR xxx[128];
		_stprintf_s(xxx, sizeof(xxx)/sizeof(TCHAR), _T("CImgViewFrame::OnCreateClient() L: %d T: %d R: %d B: %d"), rec.left, rec.top, rec.right, rec.bottom );
		OutputDebugString(xxx);
	}
#endif
	rec.right = rec.right / 5;
	rec.bottom = rec.bottom;
	CCreateContext context;
//	pContext = &context;

	context.m_pNewViewClass = RUNTIME_CLASS(CImgViewFrame);
//	context.m_pNewViewClass = RUNTIME_CLASS(CThumbWnd);
	m_SplitWnd.CreateStatic(this, 1, 2);
	m_SplitWnd.CreateView(0, 0, RUNTIME_CLASS(CThumbWnd), rec.Size(), pContext);
	rec.right = rec.right * 4;
//	context.m_pNewViewClass = RUNTIME_CLASS(CImgViewWnd);
	m_SplitWnd.CreateView(0, 1, RUNTIME_CLASS(CImgViewWnd), rec.Size(), pContext);
	m_pThumbWnd = (CThumbWnd*)m_SplitWnd.GetPane(0, 0);
	m_pViewWnd = (CImgViewWnd*)m_SplitWnd.GetPane(0, 1);
	return CFrameWnd::OnCreateClient(lpcs, pContext);
}




BOOL CImgViewFrame::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	//if(m_SplitWnd.GetPane(0, 0)->IsWindowEnabled())
	//	m_SplitWnd.GetPane(0, 0)->DestroyWindow();
	//if(m_SplitWnd.GetPane(0, 1)->IsWindowEnabled())
	//	m_SplitWnd.GetPane(0, 1)->DestroyWindow();	
	return CFrameWnd::DestroyWindow();
}

void CImgViewFrame::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class
	if(!::IsWindow(m_pThumbWnd->m_hWnd))
		delete m_pThumbWnd;
	if(!::IsWindow(m_pViewWnd->m_hWnd))
		delete m_pViewWnd;
	CFrameWnd::PostNcDestroy();
}


LRESULT CImgViewFrame::OnNcHitTest(CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	LRESULT ht = CFrameWnd::OnNcHitTest(point);
#ifdef _DEBUG
	wchar_t xxx[128];
	_stprintf_s(xxx, sizeof(xxx)/sizeof(TCHAR), _T("CImgViewFrame::OnNcHitTest() x: %d y: %d HT: %d"), point.x, point.y, ht);
	OutputDebugString(xxx);
#endif	
	if(ht == HTCLIENT)
		ht = HTCAPTION;
	return (ht);//CFrameWnd::OnNcHitTest(point);
}

void CImgViewFrame::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CFrameWnd::OnShowWindow(bShow, nStatus);

	// TODO: Add your message handler code here
	if( (bShow == TRUE) && (bFrameWindowlaunched == false) )
	{

		//this condition will be executed only once
		bFrameWindowlaunched = true;
		//this condition will be executed only once

		CRect dlgrec, rgnrec, wndrec;
		WORD uMarginTB = 2;
		m_MainDlgBar.GetWindowRect(&dlgrec);
		GetWindowRect(&wndrec);
		
		//mark the location
		CRect brec;
		
		brec.top = dlgrec.top;// + uMarginTB;
		brec.bottom = dlgrec.bottom - uMarginTB * 2;
		brec.left = dlgrec.right / 2;
		brec.right = brec.left + (dlgrec.right / 2) - 10;
		m_MainDlgBar.brec = brec;
		
		brec.DeflateRect(6,6);

		
		//create the text rgn
		CDC *pDC = m_MainDlgBar.GetDC();
		LOGFONT lf;
		memset(&lf, 0, sizeof(lf));
		lf.lfHeight = MulDiv(26, pDC->GetDeviceCaps(LOGPIXELSY), 72);
		lf.lfWeight = FW_HEAVY;
		lf.lfCharSet = ANSI_CHARSET;
		lf.lfQuality = ANTIALIASED_QUALITY;
		lf.lfPitchAndFamily = FF_DECORATIVE;
		lf.lfPitchAndFamily = lf.lfPitchAndFamily + VARIABLE_PITCH;
		lstrcpy(lf.lfFaceName, _T("Copperplate Gothic Bold"));
		CFont cfHead, cfBody, *pOldF;
		if(!cfHead.CreateFontIndirect(&lf))
			return;
		lf.lfHeight = MulDiv(10, pDC->GetDeviceCaps(LOGPIXELSY), 72);
		lf.lfWeight = FW_NORMAL;
		if(!cfBody.CreateFontIndirect(&lf))
			return;
		pOldF = (CFont*) pDC->SelectObject((CFont*)&cfHead);
		//path creation block
		pDC->BeginPath();
		//pDC->RoundRect(brec.left + 50, brec.top + 5, brec.left + 100 + brec.Width()/2, brec.bottom - 5,200, 200 );
		pDC->TextOut(brec.left + 13, brec.top + 15, _T("Image Viewer Ver 1.0. [LeadTools 13.0]"), 38);
//		pDC->TextOut(brec.left + 5, brec.top + 20, _T("Mindteck India Ltd"), 18);
		pDC->SelectObject((CFont*)&cfBody);
//		pDC->TextOutW(brec.left + 5, brec.top + 35, _T("This software is using LeadTools Library ver 13.0"), 50); 
		pDC->EndPath();
		//pDC->SelectClipPath(RGN_DIFF);
		HRGN hrgntxt = ::PathToRegion(pDC->m_hDC);
		pDC->SelectObject((CFont*)pOldF);
		pDC->ReleaseOutputDC();

		//create the small rect region
		HRGN hrgn = ::CreateRectRgn(brec.left + 10, brec.top + 10, brec.right, brec.bottom);
		HRGN hrgntxt2;

		CRect rect;
		::GetRgnBox(hrgntxt, &rect);
		hrgntxt2 = ::CreateRectRgn(rect.left, rect.top, rect.right, rect.bottom);
		HRGN hrgntxt3 = ::CreateRectRgn(0, 0, 0, 0);					//hrgntxt3 has the +tive text string
		::CombineRgn(hrgntxt3, hrgntxt, hrgntxt2, RGN_XOR);


		//create the window rgn
		HRGN hrgnWnd = ::CreateRectRgn(wndrec.left, wndrec.top, wndrec.right, wndrec.bottom);
		HRGN hrgnWndDiff = ::CreateRectRgn(0, 0, 0, 0);
		::CombineRgn(hrgnWndDiff, hrgnWnd, hrgn, RGN_XOR);
		HRGN hrgnWndTxt = ::CreateRectRgn(0, 0, 0, 0);
		::CombineRgn(hrgnWndTxt, hrgnWndDiff, hrgntxt3, RGN_OR);
		SetWindowRgn(hrgnWndTxt, TRUE);

		//create the full dlgbar rgn
		HRGN hrgnDlg = ::CreateRectRgn(dlgrec.left, dlgrec.top, dlgrec.right, dlgrec.bottom);
		HRGN hrgnDlgDiff = ::CreateRectRgn(0, 0, 0, 0);
		if(	::CombineRgn(hrgnDlgDiff, hrgn, hrgnDlg, RGN_XOR) != ERROR)
		{
			HRGN hrgnDlgTxt = ::CreateRectRgn(0, 0, 0, 0);
			::OffsetRgn(hrgntxt3, -2, -1);
			if(::CombineRgn(hrgnDlgTxt, hrgnDlgDiff, hrgntxt3, RGN_OR) != ERROR)
			{
				::OffsetRgn(hrgnDlgTxt, - 7, -7);
				m_MainDlgBar.SetWindowRgn(hrgnDlgTxt, TRUE);
			}
		}
	}
}


// //applies Alpha on the dest bitmap
HBITMAP CImgViewFrame::ApplyAlpha(HWND hWnd, HBITMAP hbmSrc, WORD wAlpha)
{
	//applying alpha
	HBITMAP hbmDest = NULL;
	BITMAP bmp;
	BLENDFUNCTION bf;
	RECT rec;
	memset(&bf, 0, sizeof(BLENDFUNCTION));
	memset(&bmp, 0, sizeof(BITMAP));
	::GetObject(hbmSrc,sizeof(BITMAP), &bmp);
	::GetClientRect(hWnd, &rec);
	HDC hDC = ::GetDC(hWnd);
	HDC hComSrcDC, hComDestDC;
	hComSrcDC = ::CreateCompatibleDC(hDC);
	hComDestDC = ::CreateCompatibleDC(hDC);

	hbmDest = ::CreateCompatibleBitmap(hComDestDC, bmp.bmWidth, bmp.bmHeight);
	HBITMAP hbmOldDest = (HBITMAP)::SelectObject(hComDestDC, hbmDest);
	HBITMAP hbmOldSrc = (HBITMAP)::SelectObject(hComSrcDC, hbmSrc);
	//now paint the destination surface white
	HBRUSH hbOld = (HBRUSH)::SelectObject(hComDestDC, ::GetStockObject(WHITE_BRUSH));
	::Rectangle(hComDestDC, 0, 0, rec.right, rec.bottom);

	memset(&bf, 0, sizeof(BLENDFUNCTION));
	bf.BlendOp = AC_SRC_OVER;
	bf.SourceConstantAlpha = wAlpha;
//	bf.AlphaFormat = AC_SRC_ALPHA;
//	if(!::AlphaBlend(hComDestDC, 0, 0, rec.right, rec.bottom, hComSrcDC, 0, 0, rec.right, rec.bottom, bf))
//		return(NULL);
	::BitBlt(hDC, 0, 0, rec.right, rec.bottom, hComSrcDC, 0, 0, SRCCOPY);
	//cleanup for alpha
	::SelectObject(hComDestDC, hbOld);
	::SelectObject(hComSrcDC, hbmOldSrc);
	::SelectObject(hComDestDC, hbmOldDest);
	::DeleteDC(hComDestDC);
	::DeleteDC(hComSrcDC);
	::ReleaseDC(hWnd, hDC);
	//end applying alpha
	return (hbmDest);
}

