// CaptionPanelBar.cpp : implementation file
//

#include "common.h"
#include <shlobj.h>
#include "ImgViewer.h"
#include "resource.h"
#include "CaptionPanelBar.h"
#include "ImgViewWnd.h"
#include "ThumbWnd.h"
#include "ImgViewFrame.h"
#include "UtilityHelper.h"
#include "gdiphelper.h"
//leadtool includes
#include "l_bitmap.h"

//leadtool includes



// CCaptionPanelBar
extern CImgWinApp theApp;


IMPLEMENT_DYNAMIC(CCaptionPanelBar, CDialogBar)

CCaptionPanelBar::CCaptionPanelBar()
: m_bLBDown(false)
, m_bHTCLIENT(false)
, m_OldPoint(0)
{
	
}

CCaptionPanelBar::~CCaptionPanelBar()
{
}


BEGIN_MESSAGE_MAP(CCaptionPanelBar, CDialogBar)
//	ON_BN_CLICKED(IDC_BUTTON_DIR, &CCaptionPanelBar::OnBnClickedButtonDir)
	ON_COMMAND(IDC_BUTTON_DIR, OnBnClickedButtonDir)
	ON_UPDATE_COMMAND_UI(IDC_BUTTON_DIR, OnUpdateButtonDir)
	ON_COMMAND(IDC_BUTTON_ALGO1, OnBnClickedAlgo1)
	ON_UPDATE_COMMAND_UI(IDC_BUTTON_ALGO1, OnUpdateButtonAlgo1)
	ON_COMMAND(IDC_BUTTON_FILE, OnBnClickedButtonFile)
	ON_UPDATE_COMMAND_UI(IDC_BUTTON_FILE, OnUpdateButtonFile)
	ON_WM_NCHITTEST()
//	ON_WM_LBUTTONDOWN()
//	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()



// CCaptionPanelBar message handlers

void CCaptionPanelBar:: OnBnClickedAlgo1()
{
	UpdateData();
}
void CCaptionPanelBar::OnUpdateButtonAlgo1(CCmdUI *pCmdUI)
{
	
}
void CCaptionPanelBar::OnUpdateButtonDir(CCmdUI *pCmdUI)
{

}

void CCaptionPanelBar::OnBnClickedButtonDir()
{
	TCHAR tchPath[256];
	TCHAR tchCurDir[256];
	LPITEMIDLIST lpidiSelectedDir = NULL;
	LPMALLOC pMalloc = NULL;
	ULONG uUsed;
	BROWSEINFO bi = {0};
	bi.lpszTitle = _T("Select Folder for image files.");
	::SHGetMalloc(&pMalloc);
	bi.hwndOwner = m_hWnd;
	memset(tchPath, 0, sizeof(tchPath));
	bi.pszDisplayName = tchPath;
	bi.ulFlags = BIF_USENEWUI;
	//get the PIDL of the current folder if the folder select dialog was opened earlier we are saving the 
	//last opened/selected folder
	//if(!csFolderDlgPath.IsEmpty())
	//{
	//	LPSHELLFOLDER lpshFolder = NULL;
	//	HRESULT hResult = ::SHGetDesktopFolder(&lpshFolder);
	//	if(SUCCEEDED(hResult))
	//	{
	//		//::GetCurrentDirectory(sizeof(tchCurDir)/sizeof(TCHAR), tchCurDir);
	//		lpshFolder->ParseDisplayName(NULL, NULL, (LPCTSTR)csFolderDlgPath, &uUsed, &lpidiSelectedDir, NULL);
	//		bi.pidlRoot = lpidiSelectedDir;
	//	}
	//	lpshFolder->Release();
	//}

	lpidiSelectedDir = ::SHBrowseForFolder(&bi);
	::SHGetPathFromIDList(lpidiSelectedDir, tchPath);
	csFolderDlgPath.Empty();
	csFolderDlgPath = tchPath;
	if(!csFolderDlgPath.IsEmpty())
		((CImgViewFrame*)theApp.m_pMainWnd)->GetThumbWnd()->UpdateCurrentFolder(tchPath);
}

BOOL CCaptionPanelBar::OnInitDialog()
{
	BOOL bRet = TRUE;
	HICON hico1, hico2, hico3;
	HICON hico = theApp.LoadIcon(IDI_ICON_FOLDER);
	((CButton*)GetDlgItem(IDC_BUTTON_DIR))->SetIcon(hico);
	hico1 = theApp.LoadIcon(IDI_ICON_LTA1);
	((CButton*)GetDlgItem(IDC_RADIO_ALGO1))->SetIcon(hico1);
	hico2 = theApp.LoadIcon(IDI_ICON_LTA2);
	((CButton*)GetDlgItem(IDC_RADIO_ALGO2))->SetIcon(hico2);
	hico3 = theApp.LoadIcon(IDI_ICON_EYE);
	((CButton*)GetDlgItem(IDC_BUTTON_FILE))->SetIcon(hico3);
	m_Brbm.LoadBitmapW(MAKEINTRESOURCE(IDB_BITMAP_DLGBR));
	m_hbrDlg.CreatePatternBrush(&m_Brbm);
	m_rad = 0;
	UpdateData(FALSE);
	return(bRet);
}

void CCaptionPanelBar::DoDataExchange(CDataExchange* pDX)
{
	OutputDebugString(_T("CCaptionPanelBar::DoDataExchange called ---------------------------------------->>"));
	// TODO: Add your specialized code here and/or call the base class
	//{{AFX_DATA_MAP(CCommdlgDlg)
	//DDX_Control(pDX, IDC_EDIT_WRITE, m_edt_write);
	//DDX_Control(pDX, IDC_EDIT_DATA_READ, m_edt_read);
	//DDX_Text(pDX, IDC_EDIT_COM_NAME, m_edt_comm_name);
	DDX_Radio(pDX, IDC_RADIO_ALGO1, m_rad);
	//DDX_Check(pDX, IDC_CHECK_READ, m_chk_read);
	//DDX_Check(pDX, IDC_CHECK_WRITE, m_chk_write);
	//}}AFX_DATA_MAP
	CDialogBar::DoDataExchange(pDX);
}

BOOL CCaptionPanelBar::Create(CWnd* pParentWnd, UINT nIDTemplate, UINT nStyle, UINT nID)
{
	// TODO: Add your specialized code here and/or call the base class

	if(!CDialogBar::Create(pParentWnd, nIDTemplate, nStyle, nID))
		return(FALSE);
	if(!OnInitDialog())
		return(FALSE);
	return(TRUE);
}

BOOL CCaptionPanelBar::Create(CWnd *pparentWnd, LPCTSTR lpszTemplateName, UINT nStyle, UINT nID)
{
	if(!CDialogBar::Create(pparentWnd, lpszTemplateName, nStyle, nID))
		return(FALSE);
	//if(!OnInitDialog())
	//	return(FALSE);
	return(TRUE);
}
void CCaptionPanelBar::OnBnClickedButtonFile()
{
	OutputDebugString(_T("Hello from CWinApp-------CImgViewFrame::OnMainDlgBarDir---------------->>"));

	OPENFILENAME ofn;
	TCHAR strFilter[1024];
	TCHAR strFilePath[300];
	TCHAR strDefExt[4];
	TCHAR strCurDir[64];
	DWORD dwErr; 
		//get the file name
	memset(&ofn, 0, sizeof(OPENFILENAME));
	//_stprintf_s(strFilter, sizeof(strFilter), _T("Monochrome Bitmap (*.bmp, *.dib)\0 *.bmp;*.dib\016 Color Bitmap   (*.bmp, *.dib)\0 *.bmp;*.dib\0256 Color Bitmap   (*.bmp, *.dib)\0 *.bmp;*.dib\024-Bit Bitmap  (*.bmp, *.dib)\0 *.bmp;*.dib\0Icon  (*.ico)\0  *.ico\0Cursor  (*.cur)\0 *.cur\0\0"));
	//memcpy_s(strFilter, sizeof(strFilter), "Monochrome Bitmap (*.bmp, *.dib)\0 *.bmp\0 16 Color Bitmap   (*.bmp, *.dib)\0 *.bmp\0 256 Color Bitmap   (*.bmp, *.dib)\0 *.bmp\0 24-Bit Bitmap  (*.bmp, *.dib)\0 *.bmp\0 Icon  (*.ico)\0  *.ico\0 Cursor  (*.cur)\0 *.cur\0\0", sizeof(strFilter));
	memset(strFilter, 0, sizeof(strFilter));
	memcpy(strFilter, _T("Tif Image (*.tif, *.tiff)\0*.tiff;*.tif\0Png Image (*.png)\0*.png\0Bitmap Image (*.bmp)\0*.bmp\0JPEG (*.jpg)\0*.jpg\0Enhanced Meta File (*.emf)\0*.emf\0All Supported Files\0*.tiff;*.tif;*.bmp;*.png;*.jpg;*.gif;*.emf;*.ico;*.cur\0\0"), 512);
	//wmemcpy_s(strFilter, sizeof(strFilter), _T("Tif Image (*.tif, *.tiff)\0*.tiff;*.tif\0Png Image (*.png)\0*.png\0Bitmap Image (*.bmp)\0*.bmp\0JPEG (*.jpg)\0*.jpg\0Enhanced Meta File (*.emf)\0*.emf\0All Supported Files\0*.tiff;*.tif;*.bmp;*.png;*.jpg;*.gif;*.emf;*.ico;*.cur\0\0"), 336);
	ofn.lStructSize = sizeof(OPENFILENAME); 
	ofn.hwndOwner = this->m_hWnd; 
	ofn.lpstrFilter = strFilter;//_T("Tif Image (*.tif, *.tiff)\0*.tiff;*.tif\0Png Image (*.png)\0*.png\0Bitmap Image (*.bmp)\0*.bmp\0JPEG (*.jpg)\0*.jpg\0Enhanced Meta File (*.emf)\0*.emf\0All Supported Files\0*.tiff;*.tif;*.bmp;*.png;*.jpg;*.gif;*.emf;*.ico;*.cur\0\0"); 
	ofn.nFilterIndex = 6;
	memset(strFilePath, 0, sizeof(strFilePath));
	ofn.lpstrFile = strFilePath; 
	ofn.nMaxFile = sizeof(strFilePath)/sizeof(TCHAR); 
	memset(strCurDir, 0, sizeof(strCurDir));
	::GetCurrentDirectory(sizeof(strCurDir), strCurDir);
	ofn.lpstrInitialDir = strCurDir;
	memset(strDefExt, 0, sizeof(strDefExt));
	wcscpy_s(strDefExt, _T("tif")); 
	//_tcscpy(strDefExt,  _T("tif")); 
	ofn.lpstrDefExt = strDefExt;
	ofn.Flags = OFN_SHOWHELP|OFN_LONGNAMES|OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST; 
	dwErr = ::GetOpenFileName(&ofn);
	if(dwErr == 0)
	{
		TCHAR xxx[256];
		_stprintf_s(xxx, _T("FileOpenDlg return: %d Extended Err: %d"), dwErr, ::CommDlgExtendedError());
		writelog(xxx);
		OutputDebugString(strDefExt);
		return; 
	}

		
	writelog(_T("ORE BABA OPENFILE KHULECHE !!!!<><><><><"));
	csImgFilePath = strFilePath;	//get the full file name and path from the file open dialog
	UINT uns = csImgFilePath.ReverseFind(_T('\\'));
	csImgFileName =  ((LPCTSTR)csImgFilePath + uns + 1);
	csImgFilePath = csImgFilePath.Left(uns + 1);

	UINT upt = csImgFileName.ReverseFind(_T('.')); 
	csImgExt = ((LPCTSTR)csImgFileName + upt + 1);

	csImgFileName = csImgFileName.Left(upt);
	OutputDebugString(csImgFileName);
	OutputDebugString(csImgExt);
	OutputDebugString(csImgFilePath);

}

void CCaptionPanelBar::OnUpdateButtonFile(CCmdUI *pCmdUI)
{

}

LRESULT CCaptionPanelBar::OnNcHitTest(CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	
	if(CWnd::OnNcHitTest(point) == HTCLIENT)
	{
		//DWORD dwlParam;
		//dwlParam = point.y;
		//dwlParam = dwlParam << 16;
		//dwlParam = dwlParam + point.x;
		//OutputDebugString(_T("WM_NCHITTEST send from Caption panel Wnd"));
		//GetParent()->SendMessage(WM_NCHITTEST, 0, (LPARAM)dwlParam);
		return(HTTRANSPARENT);
	}
	else
		return(CWnd::OnNcHitTest(point));
	//	( ((CImgViewFrame*)(GetParent()))->OnNcHitTest(point) );//CDialogBar::OnNcHitTest(point);
}


void CCaptionPanelBar::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	if(m_bLBDown == 1)
		m_bLBDown = 0;
	CDialogBar::OnLButtonDown(nFlags, point);
		DWORD dwlParam;
		ClientToScreen(&point);
		dwlParam = point.y;
		dwlParam = dwlParam << 16;
		dwlParam = dwlParam + point.x;
#ifdef _DEBUG
	wchar_t xxx[128];
	_stprintf_s(xxx, sizeof(xxx)/sizeof(TCHAR), _T("CCaptionPanelBar::OnLButtonDown() x: %d y: %d"), point.x, point.y);
	OutputDebugString(xxx);
#endif
	GetParent()->SendMessage(WM_NCLBUTTONDOWN, HTCAPTION, (LPARAM)dwlParam);
}


//void CCaptionPanelBar::OnLButtonUp(UINT nFlags, CPoint point)
//{
//	// TODO: Add your message handler code here and/or call default
//	m_bLBDown = false;
//#ifdef _DEBUG
//	wchar_t xxx[128];
//	_stprintf_s(xxx, sizeof(xxx)/sizeof(TCHAR), _T("OnLButtonUp bool: %d"), m_bLBDown);
//	OutputDebugString(xxx);
//#endif
//	CDialogBar::OnLButtonUp(nFlags, point);
//}


void CCaptionPanelBar::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	wchar_t xxx[128];	
	CPoint pt;
	pt = point;
	::ClientToScreen(this->m_hWnd, &pt);
//	CRect rec;
//	theApp.m_pMainWnd->GetWindowRect(&rec);
//
//
//	if(nFlags & MK_LBUTTON)
//	{
//		if(m_bLBDown == false)
//		{
//			m_OldPoint = pt;
//#ifdef _DEBUG
//			_stprintf_s(xxx,  sizeof(xxx)/sizeof(TCHAR), _T("WM_MOUSEMOVE 1st Down send from Caption panel Wnd =>> Y: %d X: %d"), pt.y, pt.x );
//			OutputDebugString(xxx);
//#endif
//			m_bLBDown = true;
//		}
//		else
//		{
//			DWORD dwWidth, dwHeight;
//			dwWidth = rec.Width();
//			dwHeight = rec.Height();
//#ifdef _DEBUG
//			_stprintf_s(xxx,  sizeof(xxx)/sizeof(TCHAR), _T("WM_MOUSEMOVE send from Caption panel OLD position =>> Left: %d Top: %d Right: %d Bottom: %d"), rec.left, rec.top, rec.right, rec.bottom);
//			OutputDebugString(xxx);
//#endif
//			rec.left = rec.left + (pt.x - m_OldPoint.x);
//			rec.top = rec.top + (pt.y - m_OldPoint.y);
//#ifdef _DEBUG
//			_stprintf_s(xxx,  sizeof(xxx)/sizeof(TCHAR), _T("WM_MOUSEMOVE send from Caption panel NEW position =>> Left: %d Top: %d Right: %d Bottom: %d"), rec.left, rec.top, rec.right, rec.bottom);
//			OutputDebugString(xxx);
//#endif
//			//theApp.m_pMainWnd->SendMessage(WM_MOUSEMOVE, nFlags, (LPARAM)dwlParam);
//			theApp.m_pMainWnd->MoveWindow(rec.left, rec.top, dwWidth, dwHeight);
//			m_OldPoint = pt;
//		}
//	}
	CDialogBar::OnMouseMove(nFlags, point);
}

void CCaptionPanelBar::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	{
#ifdef _DEBUG
		wchar_t xxx[128];
			_stprintf_s(xxx,  sizeof(xxx)/sizeof(TCHAR), _T(" CCaptionPanelBar::OnPaint()  Left: %d Top: %d Right: %d Bottom: %d"), brec.left, brec.top, brec.right, brec.bottom);
			OutputDebugString(xxx);
#endif
	}

	//dc.DrawEdge(&brec, EDGE_RAISED, BF_LEFT); 
	//dc.DrawEdge(&brec, EDGE_RAISED, BF_TOP); 
	//dc.DrawEdge(&brec, EDGE_RAISED, BF_RIGHT); 
	//dc.DrawEdge(&brec, EDGE_RAISED, BF_BOTTOM); 
	 //(brec.left + 2, brec.top + 2, _T("Some Text"), 9);
	//	dc.Rectangle(brec.left + 15, brec.top + 15, brec.right/2 - 10, brec.bottom - 15);
//	dc.DrawFrameControl(&brec, DFC_BUTTON, DFCS_BUTTONCHECK);
	// Do not call CDialogBar::OnPaint() for painting messages
}


HBRUSH CCaptionPanelBar::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	//HBRUSH hbr;// = CDialogBar::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	
	//hbr = ::CreatePatternBrush(::LoadBitmap(theApp.m_hInstance, MAKEINTRESOURCE(IDB_BITMAP_DLGBR)));
	// TODO:  Return a different brush if the default is not desired
	return (HBRUSH)m_hbrDlg;
}
