/*
	declaration of CWinApp derived class CImgWinApp for the message pump and the main window pointer
*/

#ifndef _CIMG_WINAPP
#define _CIMG_WINAPP

class CImgWinApp : public CWinApp
{
public:
	CImgWinApp();
	wchar_t strLogPath[128];

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGadgetTipApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

	//Implementation
	//{{AFX_MSG(CImgWinApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//some global declaration
void writelog(LPCTSTR strMessage, bool bTimeStamp = true);

#endif //_CIMG_WINAPP