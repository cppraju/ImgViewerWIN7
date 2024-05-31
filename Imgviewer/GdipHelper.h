#pragma once

// CGdipHelper command target















class CGdipHelper : public CObject
{
	static CGdipHelper *pthis;
	static ULONG_PTR gdipToken;						//gdiplus token
	static GdiplusStartupInput gdip_Startup;		//gdiplus init 


public:
	CGdipHelper();
	virtual ~CGdipHelper();

	//create destroy
	static CGdipHelper * GetInstance(void);
	static void DeleteInstance(void);



	//functionality
	bool SaveHBITMAP(HBITMAP hbm);
	bool GetEncoderClsid(wchar_t *pwstrMIME, CLSID *pclsID);
	short PrepareThumbnails(CImageList & imglst, short sWidth, short sHeight, const CList<CString, CString> & filelst);
};


