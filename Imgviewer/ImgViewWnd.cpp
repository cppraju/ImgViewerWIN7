// ImgViewWnd.cpp : implementation file
//

#include "common.h"
#include "ImgViewer.h"
#include "ImgViewWnd.h"
#include "ThumbWnd.h"
#include "resource.h"
#include "CaptionPanelBar.h"
#include "ImgViewFrame.h"

#include "GdipHelper.h"


// CImgViewWnd
extern CImgWinApp theApp;

IMPLEMENT_DYNCREATE(CImgViewWnd, CWnd)

CImgViewWnd::CImgViewWnd()
{

}

CImgViewWnd::~CImgViewWnd()
{
}


BEGIN_MESSAGE_MAP(CImgViewWnd, CWnd)
	ON_WM_SHOWWINDOW()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CImgViewWnd message handlers



BOOL CImgViewWnd::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: Add your specialized code here and/or call the base class
	memset(&wc, 0, sizeof(WNDCLASS));
	wc.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = ::DefWindowProc;
	wc.hInstance = AfxGetInstanceHandle();
	hbmbk = ::LoadBitmap(theApp.m_hInstance, MAKEINTRESOURCE(IDB_BITMAP_ALPHABK));
	hb = ::CreatePatternBrush(hbmbk);
	wc.hbrBackground = (HBRUSH)hb;
	//leaving the cursor as NULL
	hCursorMove = LoadCursor(wc.hInstance, MAKEINTRESOURCE(IDC_CURSOR_MOVE4WAY));
	hCursor = LoadCursor(wc.hInstance, MAKEINTRESOURCE(IDC_CURSOR_PIXEL));
	wc.lpszClassName = _T("ImgViewWndClass");
	AfxRegisterClass(&wc);
	dwStyle = dwStyle|WS_BORDER;
	return CWnd::Create(_T("ImgViewWndClass"), lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}
/*
	This will prepare a transperant bitmap to be used as a brush for the window background
*/
HBITMAP CImgViewWnd::PrepareAlphaBitmap(void)
{
	HBITMAP hbm ;
	HDC hdc = ::GetDC(this->m_hWnd);
	RECT rec;
	::GetClientRect(this->m_hWnd, &rec);

	hbm = ::CreateCompatibleBitmap(hdc, rec.right, rec.bottom);
	hbmAlpha =  ::CreateCompatibleBitmap(hdc, rec.right, rec.bottom);
	HDC hdcCom = ::CreateCompatibleDC(hdc);

	HBITMAP hbmOld = (HBITMAP)::SelectObject(hdcCom, hbm);
	HBRUSH hb = ::CreateSolidBrush(RGB(255, 0, 128));
	HBRUSH hbOld = (HBRUSH)::SelectObject(hdcCom, hb);
	::Rectangle(hdcCom, 0, 0, rec.right, rec.bottom);
	//::SelectObject(hdcCom, hbOld);
	//hbm = (HBITMAP)::SelectObject(hdcCom, hbmOld);
	//hbmAlpha = ((CImgViewFrame*)theApp.m_pMainWnd)->ApplyAlpha(this->m_hWnd, hbm, 40);
	
	//::SelectObject(hdcCom, hbm);
	//::BitBlt(hdc, 0, 0, rec.right, rec.bottom, hdcCom, 0, 0, SRCCOPY);
	BLENDFUNCTION bf;
	memset(&bf, 0, sizeof(BLENDFUNCTION));
	bf.BlendOp = AC_SRC_OVER;
	bf.SourceConstantAlpha = 40;

	::AlphaBlend(hdc, 0, 0, rec.right, rec.bottom, hdcCom, 0, 0, rec.right, rec.bottom, bf);

	::SelectObject(hdcCom, hbmAlpha);
	::BitBlt(hdcCom, 0, 0, rec.right, rec.bottom, hdc, 0, 0, SRCCOPY);

	//cleanup
	::SelectObject(hdcCom, hbmOld);
	::SelectObject(hdcCom, hbOld);
	::DeleteObject(hb);
	::DeleteDC(hdcCom);
	::ReleaseDC(this->m_hWnd, hdc);

	CGdipHelper::GetInstance()->SaveHBITMAP(hbmAlpha);
	return(hbmAlpha);
}
BOOL CImgViewWnd::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Add your specialized code here and/or call the base class
//	cs.style = cs.style | WS_VSCROLL | WS_HSCROLL;

	return CWnd::PreCreateWindow(cs);
}

void CImgViewWnd::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CWnd::OnShowWindow(bShow, nStatus);

	// TODO: Add your message handler code here
	SetClassLong(this->m_hWnd, GCL_HCURSOR,(long) hCursor);
	
}

void CImgViewWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CWnd::OnMouseMove(nFlags, point);
}

void CImgViewWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	SetClassLong(this->m_hWnd, GCL_HCURSOR,(long) hCursorMove);
	SetCursor(hCursorMove);

	//CClientDC dc(this);
	//
	//CDC dcCompat;
	//dcCompat.CreateCompatibleDC(&dc);
	//CBitmap *bmA;
	//bmA = CBitmap::FromHandle(hbmAlpha);
	//CBitmap *pOldBM = dcCompat.SelectObject(bmA);
	//RECT rec;
	//::GetClientRect(this->m_hWnd, &rec);
	//dc.BitBlt(0, 0, rec.right, rec.bottom, &dcCompat, 0, 0, SRCCOPY);
	//dcCompat.SelectObject(pOldBM);
	//dcCompat.DeleteDC();
	//bmA->DeleteObject();

	//hbmAlpha = PrepareAlphaBitmap();
	//Invalidate();
	CWnd::OnLButtonDown(nFlags, point);
}

void CImgViewWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	SetClassLong(this->m_hWnd, GCL_HCURSOR,(long) hCursor);
	SetCursor(hCursor);

	CWnd::OnLButtonUp(nFlags, point);
}

void CImgViewWnd::OnPaint()
{
	writelog(_T("CImgViewWnd::OnPaint() ------------------POSTED-------------------->> getting called"));
	//BLENDFUNCTION bf;
	//memset(&bf, 0, sizeof(BLENDFUNCTION));
	//bf.BlendOp = AC_SRC_OVER;
	//bf.SourceConstantAlpha = 40;
	
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
//	CDC dcCompat;
//	dcCompat.CreateCompatibleDC(&dc);
//	CBitmap *bmA;
//	bmA = CBitmap::FromHandle(hbmAlpha);
//	CBitmap *pOldBM = (CBitmap*)dcCompat.SelectObject(bmA);
//	RECT rec;
//	::GetClientRect(this->m_hWnd, &rec);
//	//CBrush cbr;
//	//cbr.CreateSolidBrush(RGB(255, 255, 0));
//	//CBrush *cbOld = dc.SelectObject(&cbr);
//	//dc.Rectangle(0, 0, rec.right, rec.bottom);
////	dc.AlphaBlend(0, 0, rec.right, rec.bottom, &dcCompat, 0, 0, rec.right, rec.bottom, bf);
//	dc.BitBlt(0, 0, rec.right, rec.bottom, &dcCompat, 0, 0, SRCCOPY);
//	dcCompat.SelectObject(pOldBM);
//	bmA->DeleteObject();
//	dcCompat.DeleteDC();
	// Do not call CWnd::OnPaint() for painting messages
}
