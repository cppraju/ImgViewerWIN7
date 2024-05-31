#pragma once

// CUtilityHelper command target


enum SEARCHFILETYPE
{
	ALL			= 0x00000100,
	BMP			= 0x00000001,
	JPG			= 0x00000002,
	PNG			= 0x00000004,
	TIF			= 0x00000008,
	GIF			= 0x00000010,
	EMF			= 0x00000020,
	ICO			= 0x00000040,
	CUR			= 0x00000080
};



class CUtilityHelper : public CObject
{
	static CUtilityHelper *pthis;
public:
	CUtilityHelper();
	virtual ~CUtilityHelper();

//construction destruction
	static CUtilityHelper * GetInstance(void);
	static void DeleteInstance(void);

//functionality
	INT_PTR FindImageFilesInFolder(const CString csPath, CList<CString, CString> &filelst, SEARCHFILETYPE type = ALL);
};


