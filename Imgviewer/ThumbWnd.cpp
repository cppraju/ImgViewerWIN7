// ThumbWnd.cpp : implementation file
//


#include "common.h"
#include "ImgViewer.h"
#include "resource.h"
#include "CaptionPanelBar.h"
#include "ImgViewWnd.h"
#include "ThumbWnd.h"

#include "ImgViewFrame.h"

#include "UtilityHelper.h"
#include "gdiphelper.h"

// CThumbWnd



extern CImgWinApp theApp;


IMPLEMENT_DYNCREATE(CThumbWnd, CListCtrl)

CThumbWnd::CThumbWnd()
{
	
}

CThumbWnd::~CThumbWnd()
{
}


BEGIN_MESSAGE_MAP(CThumbWnd, CListCtrl)
//	ON_WM_CTLCOLOR()
ON_WM_MOUSEMOVE()
ON_NOTIFY_REFLECT(LVN_INSERTITEM, &CThumbWnd::OnLvnInsertitem)
END_MESSAGE_MAP()



// CThumbWnd message handlers

bool CThumbWnd::LoadThumbNailsFromFolder(void)
{
	bool bRet = false;
	int i = 0;
	int count = m_ImgLst.GetImageCount();
	while(i < count)
	{
		HICON hIcon = NULL;
		hIcon = m_ImgLst.ExtractIcon(i);
		m_IcoLst.Add(hIcon);
		i = i + 1;
	}
	SetImageList(&m_IcoLst, LVSIL_NORMAL);
	//add items to the listctrl
	LV_ITEM lvi;
	memset(&lvi, 0, sizeof(LV_ITEM));
	int index;
	for(i = 0; i < count; i = i + 1)
	{
		lvi.mask = LVIF_IMAGE;
		lvi.iImage = i;
		lvi.iItem = i;
		OutputDebugString(_T("CThumbWnd BEFORE InsertItem() *******************************>>>>"));
		index = InsertItem(&lvi);

	}
		

#ifdef _DEBUG
	CPoint pt;
	pt.x = 10;
	pt.y = 10;
	CRect rec, rec2;
	CDC *pDC = (((CImgViewFrame*)theApp.m_pMainWnd)->GetImgViewWnd())->GetDC();
	 (((CImgViewFrame*)theApp.m_pMainWnd)->GetImgViewWnd())->GetClientRect(&rec);
	
	GetClientRect(&rec2);
	for(UINT i = 0; i < m_ImgLst.GetImageCount(); i = i + 1)
	{
		m_ImgLst.Draw(pDC, i, pt, ILD_NORMAL);
		if(rec.right - (pt.x + ((rec2.right/3)*2 + 5)) > ((rec2.right/3)*2 + 5))
			pt.x = pt.x + ((rec2.right/3)*2 + 5);
		else
		{
			pt.x = 10;
			pt.y = pt.y + ((rec2.right/3)*2 + 5);
		}
	}
	pDC->ReleaseOutputDC();
#endif


	return(bRet);
}

BOOL CThumbWnd::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: Add your specialized code here and/or call the base class
	memset(&wc, 0, sizeof(WNDCLASS));
	wc.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = AfxWndProc;
	wc.hInstance = AfxGetInstanceHandle();
	wc.hbrBackground = (HBRUSH)NULL;//(COLOR_WINDOW + 1);
	wc.hCursor = LoadCursor(wc.hInstance, IDC_CROSS);
	wc.lpszClassName = _T("ThumbViewWndClass");
	AfxRegisterClass(&wc);
	if(CWnd::Create(lpszClassName, lpszWindowName, dwStyle|LVS_ICON, rect, pParentWnd, nID, pContext))
		OnInitialUpdate();
	return(TRUE);
}

void CThumbWnd::OnInitialUpdate()
{
	//	CListCtrl::OnInitialUpdate();
	// TODO: Add your specialized code here and/or call the base class
	OutputDebugString(_T("CThumbWnd::OnInitialUpdate *******************************>>>>"));
	bm.LoadBitmapW(MAKEINTRESOURCE(IDB_BITMAP_THUMBBR));

	br.CreatePatternBrush(&bm);
	HBRUSH hb = (HBRUSH)br;
#ifdef _DEBUG
	::SetLastError(0);
#endif
	DWORD dwRet = ::SetClassLongPtr(m_hWnd, GCL_HBRBACKGROUND, (LONG_PTR)(HBRUSH)br);
	hCurGrip = ::LoadCursor(theApp.m_hInstance, MAKEINTRESOURCE(IDC_CURSOR_SELECT));
	dwRet = ::SetClassLong(this->m_hWnd, GCL_HCURSOR, (LONG_PTR)hCurGrip);
	DWORD dwStyle;
	dwStyle = ::GetWindowLong(m_hWnd, GWL_STYLE);
	::SetWindowLong(m_hWnd, GWL_STYLE, dwStyle|LVS_ICON);
	::SetCursor(hCurGrip);
#ifdef _DEBUG
	{
		TCHAR xxx[128];
		_stprintf_s(xxx, sizeof(xxx)/sizeof(TCHAR), _T("CThumbWnd::OnInitialUpdate() SetClassLong Return: %d LastErr: %d"), dwRet, ::GetLastError());
		writelog(xxx);
	}
#endif
	CRect rec;
	GetClientRect(&rec);
	OutputDebugString(_T("CThumbWnd BEFORE InsertColumn() *******************************>>>>"));
	int x = InsertColumn(0, _T("Image Thumbnails"), LVCFMT_CENTER, rec.right);
}

void CThumbWnd::UpdateCurrentFolder(const TCHAR *ptchCurrentDir)
{
	if(lstImgFile.GetCount() > 0)
	{
		lstImgFile.RemoveAll();
		m_ImgLst.DeleteImageList();
		m_IcoLst.DeleteImageList();
	}
	lstrcpy(tchPath, ptchCurrentDir);

	(CUtilityHelper::GetInstance())->FindImageFilesInFolder(tchPath, lstImgFile);
	POSITION pos = lstImgFile.GetHeadPosition();
	for(int i = 0; i < lstImgFile.GetCount(); i = i + 1)
		writelog(lstImgFile.GetNext(pos));
	//get the window rect
	CRect rec;
	GetClientRect(&rec);
	m_ImgLst.Create((rec.right/3)*2, (rec.right/3)*2, ILC_COLORDDB|ILC_MASK, lstImgFile.GetCount(), lstImgFile.GetCount()/10);
	m_IcoLst.Create((rec.right/3)*2, (rec.right/3)*2, ILC_COLORDDB|ILC_MASK, lstImgFile.GetCount(), lstImgFile.GetCount()/10);
	short sImgCnt = CGdipHelper::GetInstance()->PrepareThumbnails(m_ImgLst, (rec.right/3)*2, (rec.right/3)*2, lstImgFile);
	//ifsImgCnt == lstImgFile.GetCount() then thumbnails for all the files are generated
	//set the CImageList with the listctrl
	LoadThumbNailsFromFolder();
}


//HBRUSH CThumbWnd::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
//{
//	HBRUSH hbr = CListCtrl::OnCtlColor(pDC, pWnd, nCtlColor);
//	writelog(_T("CThumbWnd::OnCtlColor *******************************>>>>"));
//	// TODO:  Change any attributes of the DC here
//	bm.LoadBitmapW(MAKEINTRESOURCE(IDB_BITMAP_BKFRAME_BRUSH));
//	br.CreatePatternBrush(&bm);
//	hbr = (HBRUSH)br;
//	// TODO:  Return a different brush if the default is not desired
//	return hbr;
//}

void CThumbWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	
	CListCtrl::OnMouseMove(nFlags, point);
}


void CThumbWnd::OnLvnInsertitem(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	OutputDebugString(_T("CThumbWnd::OnLvnInsertitem *******************************>>>>"));
	*pResult = 0;
}
