// UtilityHelper.cpp : implementation file
//

#include "common.h"
#include "ImgViewer.h"
#include "UtilityHelper.h"


// CUtilityHelper
CUtilityHelper * CUtilityHelper::pthis = NULL;

CUtilityHelper::CUtilityHelper()
{
}

CUtilityHelper::~CUtilityHelper()
{
}


// CUtilityHelper member functions
//construction destruction
CUtilityHelper * CUtilityHelper::GetInstance(void)
{
	if(pthis == NULL)
		pthis = new CUtilityHelper();
	return(pthis);
}
void CUtilityHelper::DeleteInstance(void)
{
	if(pthis != NULL)
		delete(pthis);
	pthis = NULL;
}

//functionality
/*
	csPath	the root path to search	
	filelst		reference to a CList for a list of files
	type		type of image files to be considered
	returns -1 if an error occurs else the no file of matching type is found
*/
INT_PTR CUtilityHelper::FindImageFilesInFolder(const CString csPath, CList<CString, CString> &filelst, SEARCHFILETYPE type)
{
	INT_PTR sFileCnt = -1;
	WIN32_FIND_DATA fdata;
	TCHAR tchExt[5], tFileName[MAX_PATH];
	HANDLE hf = NULL;
	::SetLastError(0);
	filelst.RemoveAll();
	wchar_t *ptchContext = NULL;
	CString cs = csPath;
	switch(type)
	{
	case ALL:
		cs = cs + _T("\\*.*");;
		break;
	case BMP:
		cs = cs + _T("\\*.bmp");
		break;
	case JPG:
		cs = cs + _T("\\*.jpg");
		break;
	case PNG:
		cs = cs + _T("\\*.png");
		break;
	case TIF:
		cs = cs + _T("\\*.tif");
		break;
	case GIF:
		cs = cs + _T("\\*.gif");
		break;
	case EMF:
		cs = cs + _T("\\*.emf");
		break;
	case ICO:
		cs = cs + _T("\\*.ico");
		break;
	case CUR:
		cs = cs + _T("\\*.bmp");
		break;
	}
	memset(&fdata, 0, sizeof(WIN32_FIND_DATA));
	hf = ::FindFirstFile(cs, &fdata);
	if(hf == INVALID_HANDLE_VALUE)
	{
		wchar_t xxx[128];
		memset(xxx, 0, sizeof(xxx));
		//_stprintf(xxx, _T("CUtilityHelper::FindFilesInFolder() FindFirstFile() LastErr: %d"), ::GetLastError());
		_stprintf_s(xxx, sizeof(xxx), _T("CUtilityHelper::FindFilesInFolder() FindFirstFile() LastErr: %d"), ::GetLastError());
		writelog(xxx);
		return(sFileCnt);
	} 
	do
	{
		memset(tchExt, 0, sizeof(TCHAR[5]));
		memset(tFileName, 0, sizeof(TCHAR[MAX_PATH]));
		lstrcpy(tFileName, fdata.cFileName);
		//get the extension
		wchar_t *pwch = NULL;
		pwch = tFileName + lstrlen(tFileName);
		while(*(pwch-1) != _T('.'))
			pwch--;
		
//		_tcstok_s(tFileName, _T("."), &ptchContext);
		lstrcpy(tchExt, pwch);
		
		if(type & ALL)
		{
			if( (lstrcmpi(tchExt, _T("BMP")) == 0) || (lstrcmpi(tchExt, _T("JPG")) == 0) || (lstrcmpi(tchExt, _T("JPEG")) == 0) || (lstrcmpi(tchExt, _T("PNG")) == 0) || (lstrcmpi(tchExt, _T("TIF")) == 0) || 
				(lstrcmpi(tchExt, _T("TIFF")) == 0) || (lstrcmpi(tchExt, _T("GIF")) == 0) || (lstrcmpi(tchExt, _T("EMF")) == 0) || (lstrcmpi(tchExt, _T("ICO")) == 0) || (lstrcmpi(tchExt, _T("CUR")) == 0) )
			{
				cs = csPath;
				cs = cs + _T("\\");
				cs = cs + fdata.cFileName;
				filelst.AddTail(cs);
			}
		}
		else if(type & BMP)
		{
			if(lstrcmpi(tchExt, _T("BMP")) == 0)
			{
				cs = csPath;
				cs = cs + _T("\\");
				cs = cs + fdata.cFileName;
				filelst.AddTail(cs);
			}
		}
		else if(type & JPG)
		{
			if(  (lstrcmpi(tchExt, _T("JPG")) == 0) || (lstrcmpi(tchExt, _T("JPEG")) == 0) )
			{
				cs = csPath;
				cs = cs + _T("\\");
				cs = cs + fdata.cFileName;
				filelst.AddTail(cs);
			}
		}		
		else if(type & PNG)
		{
			if(lstrcmpi(tchExt, _T("PNG")) == 0)
			{
				cs = csPath;
				cs = cs + _T("\\");
				cs = cs + fdata.cFileName;
				filelst.AddTail(cs);
			}
		}	
		else if(type & TIF)
		{
			if(  (lstrcmpi(tchExt, _T("TIF")) == 0) || (lstrcmpi(tchExt, _T("TIFF")) == 0) )
			{
				cs = csPath;
				cs = cs + _T("\\");
				cs = cs + fdata.cFileName;
				filelst.AddTail(cs);
			}
		}	
		else if(type & GIF)
		{
			if(lstrcmpi(tchExt, _T("GIF")) == 0)
			{
				cs = csPath;
				cs = cs + _T("\\");
				cs = cs + fdata.cFileName;
				filelst.AddTail(cs);
			}
		}	
		else if(type & EMF)
		{
			if(lstrcmpi(tchExt, _T("EMF")) == 0)
			{
				cs = csPath;
				cs = cs + _T("\\");
				cs = cs + fdata.cFileName;
				filelst.AddTail(cs);
			}
		}	
		else if(type & ICO)
		{
			if(lstrcmpi(tchExt, _T("ICO")) == 0)
			{
				cs = csPath;
				cs = cs + _T("\\");
				cs = cs + fdata.cFileName;
				filelst.AddTail(cs);
			}
		}	
		else if(type & CUR)
		{
			if(lstrcmpi(tchExt, _T("CUR")) == 0)
			{
				cs = csPath;
				cs = cs + _T("\\");
				cs = cs + fdata.cFileName;
				filelst.AddTail(cs);
			}
		}	

		memset(&fdata, 0, sizeof(WIN32_FIND_DATA));
		::SetLastError(0);
	}
	while(::FindNextFile(hf, &fdata));
	if(GetLastError() == ERROR_NO_MORE_FILES)
		sFileCnt = filelst.GetCount();
	//if(ptchContext != NULL)
	//	delete(ptchContext);
	::FindClose(hf);
	return(sFileCnt);
}

