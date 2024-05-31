#pragma once

// CLeadToolWrapper command target

class CLeadToolWrapper : public CObject
{
	static CLeadToolWrapper *pthis;
public:
	CLeadToolWrapper();
	virtual ~CLeadToolWrapper();

	
	//create destroy
	static CLeadToolWrapper * GetInstance(void);
	static void DeleteInstance(void);

	//functionality
	bool GetFolderThumbnails(CImageList &imglst);


};


