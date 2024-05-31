// LeadToolWrapper.cpp : implementation file
//

#include "common.h"
#include "ImgViewer.h"

//leadtool includes
#include "Ltfil.h"
#include "Ltdis.h"
#include "LTIMG.H"
//leadtool includes

#include "LeadToolWrapper.h"


// CLeadToolWrapper
CLeadToolWrapper* CLeadToolWrapper::pthis = NULL;

CLeadToolWrapper::CLeadToolWrapper()
{

}

CLeadToolWrapper::~CLeadToolWrapper()
{

}


// CLeadToolWrapper member functions
CLeadToolWrapper * CLeadToolWrapper::GetInstance(void)
{
	if(pthis == NULL)
	{
		pthis = new CLeadToolWrapper();
	}
	return(pthis);
}


bool CLeadToolWrapper::GetFolderThumbnails(CImageList &imglst)
{
	bool bRet = false;



	return(bRet);
}

void CLeadToolWrapper::DeleteInstance(void)
{
	if(pthis != NULL)
		delete(pthis);
	pthis = NULL;
}

	