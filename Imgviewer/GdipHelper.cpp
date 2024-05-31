// GdipHelper.cpp : implementation file
//

#include "common.h"
#include "ImgViewer.h"
#include "GdipHelper.h"


// CGdipHelper
CGdipHelper * CGdipHelper::pthis = NULL;
ULONG_PTR CGdipHelper::gdipToken;						//gdiplus token
GdiplusStartupInput CGdipHelper::gdip_Startup;		//gdiplus init 

CGdipHelper::CGdipHelper()
{

}

CGdipHelper::~CGdipHelper()
{

}


// CGdipHelper member functions
CGdipHelper * CGdipHelper::GetInstance(void)
{
	if(pthis == NULL)
	{
		::GdiplusStartup(&gdipToken, &gdip_Startup, 0);
		pthis = new CGdipHelper();
	}
	return(pthis);
}
void CGdipHelper::DeleteInstance(void)
{
	if(pthis != NULL)
	{
		::GdiplusShutdown(gdipToken);
		delete(pthis);
		pthis = NULL;
	}

}
bool CGdipHelper::SaveHBITMAP(HBITMAP hbm)
{
	bool bRet = false;

	//gd+
	Bitmap gdip_bmp(hbm, NULL);
	CLSID clsid_png;
	GetEncoderClsid(L"image/png", &clsid_png);
	Status sRet = Ok;
	if(gdip_bmp.Save(L".\\hbmalpha.png", &clsid_png, 0) == sRet)
		bRet = true;
	return(bRet);
	//gdi+
}

bool CGdipHelper::GetEncoderClsid(wchar_t *pwstrMIME, CLSID *pclsID)
{
	bool bRet = false;
	_CrtMemState c1, c2, c3;
	ImageCodecInfo *pImgCodecInfo = NULL;
	UINT numEncoders, sizeEncoders;
	_CrtMemCheckpoint(&c1);
	GetImageEncodersSize(&numEncoders, &sizeEncoders);
	pImgCodecInfo = (ImageCodecInfo*) malloc(sizeEncoders);
	GetImageEncoders(numEncoders, sizeEncoders, pImgCodecInfo);
	//now we have a list of all the supported encoders
	UINT i;
	for(i = 0; i < numEncoders; i = i + 1)
	{
		if(wcscmp((pImgCodecInfo + i)->MimeType, pwstrMIME))
			break;
	}
	if(i < numEncoders)
	{
		*pclsID = (pImgCodecInfo + i)->Clsid;
		bRet = true;
	}
	free(pImgCodecInfo);
	_CrtMemCheckpoint(&c2);
	_CrtMemDifference(&c3, &c1, &c2);
	_CrtMemDumpStatistics(&c3);
	return(bRet);
}
/*
	imglst		ref to a imagelist that will be filled with thumbnails of images from filelst
	sWidth		width of images in the image list
	sHeight		height of images in the image list
	filelst			list of files whose thumbnails will be generated
	return		count of total thumbnails generated else if error then -1
*/
short CGdipHelper::PrepareThumbnails(CImageList & imglst, short sWidth, short sHeight, const CList<CString, CString> & filelst)
{
	short sCnt = 0;
	CString csF, csT;
	CLSID cls_bmp;
	HRESULT hr;
	IStream *pStream = NULL;
	IStorage *pStorage = NULL;
	GetEncoderClsid(_T("image/bmp"), &cls_bmp);
	POSITION pos = filelst.GetHeadPosition();
	Gdiplus::Status s = Gdiplus::Status::Ok;
	hr = ::CoInitialize(NULL);

	
	while(sCnt < filelst.GetCount())
	{
		csF = filelst.GetNext(pos);
		Bitmap img(csF);
		Image *pimg = img.GetThumbnailImage(sWidth, sHeight, NULL, NULL);
		hr = StgCreateDocfile(L"CompoundFile.cmp", STGM_READWRITE|STGM_SHARE_EXCLUSIVE, 0, &pStorage);
		hr = pStorage->CreateStream(L"ImageStream", STGM_READWRITE|STGM_SHARE_EXCLUSIVE, 0, 0, &pStream);
		pimg->Save(pStream, &cls_bmp, NULL);
		Bitmap bT(pStream);
		csT.Format(_T(".\\thumb_%03d.bmp"), sCnt);
#ifdef _DEBUG
		s = bT.Save(csT, &cls_bmp, NULL);
		if(s != Gdiplus::Status::Ok)
		{
			sCnt = -1;
			break;
		}
#endif
		//get the HBITMAP from the Bitmap object
		HBITMAP hbm = NULL;
		bT.GetHBITMAP(NULL, &hbm);
		CBitmap *pbm = CBitmap::FromHandle(hbm);
		imglst.Add(pbm, RGB(0, 0, 0));	//RGB(55, 74, 81)

		//insert 
		sCnt = sCnt + 1;
		pStream->Release();
		pStorage->Release();
		::DeleteFile(L"CompoundFile.cmp");
	}
	return sCnt;
}
