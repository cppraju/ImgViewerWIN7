/*
	definition of CWinApp derived class CImgWinApp for the message pump and the main window pointer
*/
#include "common.h"
#include "ImgViewer.h"

#include "ImgViewWnd.h"
#include "ThumbWnd.h"
#include "resource.h"
#include "CaptionPanelBar.h"
#include "ImgViewFrame.h"

#include "GdipHelper.h"
#include "LeadToolWrapper.h"
#include "UtilityHelper.h"

BEGIN_MESSAGE_MAP(CImgWinApp, CWinApp)
	//{{AFX_MSG_MAP(CGadgetTipApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CImgWinApp::CImgWinApp()
{
	
}

BOOL CImgWinApp::InitInstance()
{
	BOOL bRet = FALSE;


	

	//CCommandLineInfo ccmd;
	//ParseCommandLine(ccmd);
	//OutputDebugString(_T("Hello from CWinApp----------------------->>"));
	////m_pMainWnd
	//if(!ProcessShellCommand(ccmd))
	//	return(FALSE);
	::GetCurrentDirectory(sizeof(strLogPath), strLogPath);
	wcscat_s(strLogPath, _T("\\imgviewer_LT.log"));
	//attach the one main window
	m_pMainWnd  = new CImgViewFrame();
	CString cs;
	HICON hico = LoadIcon(MAKEINTRESOURCE(IDI_ICON_FOLDER));
	cs.LoadStringW(AfxGetInstanceHandle(), AFX_IDS_APP_TITLE);
	TCHAR wStyle[256];
	LPCTSTR lpStyle = AfxRegisterWndClass(CS_DBLCLKS|CS_OWNDC); ;
//	memset(wStyle, 0, sizeof(wStyle));
//	wStyle = AfxRegisterWndClass(CS_DBLCLKS|CS_OWNDC); 
	WORD cxsc, cysc;
	cxsc = ::GetDeviceCaps(::GetDC(NULL), HORZRES);
	cysc = ::GetDeviceCaps(::GetDC(NULL), VERTRES);
	CRect rec;
	rec.left = rec.top = 0;
	rec.right = cxsc * .97;//900;
	rec.bottom = cysc * .97;//900;
	((CImgViewFrame*)m_pMainWnd)->Create(lpStyle, _T(""), WS_POPUP|WS_BORDER|WS_THICKFRAME|WS_VISIBLE, rec);
//	((CImgViewFrame*)m_pMainWnd)->Create(NULL, cs);
	((CImgViewFrame*)m_pMainWnd)->SetIcon(hico, FALSE);
	m_pMainWnd->ShowWindow(SW_SHOW);

	return(TRUE);
}

CImgWinApp theApp;

int CImgWinApp::ExitInstance()
{
	// TODO: Add your specialized code here and/or call the base class
	CGdipHelper::DeleteInstance();
	CLeadToolWrapper::DeleteInstance();
	CUtilityHelper::DeleteInstance();

	return CWinApp::ExitInstance();
}

void writelog(LPCTSTR strMessage, bool bTimeStamp)
{
#ifdef _DEBUG
	CStdioFile csf;
	CFileException e;
	wchar_t strFileName[64];
	CString strDebugTextToLog;
	CString csMsg = strMessage;
	memset(strFileName, 0, sizeof(strFileName));
	if(bTimeStamp)
	{
		COleDateTime dtTime = COleDateTime::GetCurrentTime();
		strDebugTextToLog.Format(L"%2d/%2d/%4d %02d:%02d:%02d - ",dtTime.GetMonth(),dtTime.GetDay(),dtTime.GetYear(), dtTime.GetHour(), dtTime.GetMinute(), dtTime.GetSecond());
	}
	strDebugTextToLog += csMsg;
	OutputDebugString(strDebugTextToLog);
	csMsg = strDebugTextToLog;
	strDebugTextToLog.Format(L"\n%s", csMsg);
	if(!csf.Open(theApp.strLogPath, CFile::modeCreate|CFile::modeReadWrite|CFile::typeText|CFile::shareDenyWrite|CFile::modeNoTruncate, &e))
	{
		wchar_t strErr[64];
		memset(strErr, 0, sizeof(strErr));
		e.GetErrorMessage(strErr, sizeof(strErr));
		TRACE((L"\nFailed to open file Error Code:%s"), strErr);
		memset(strErr, 0, sizeof(strErr));
		//we will just attempt to create the file and use the handle in the CFile derived object
		::SetLastError(0);
		HANDLE hFile = ::CreateFile(strFileName, GENERIC_WRITE|GENERIC_READ, FILE_SHARE_READ, NULL, 
			OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL|FILE_FLAG_RANDOM_ACCESS, NULL);
		if(hFile == INVALID_HANDLE_VALUE)
		{
			swprintf_s(strErr, sizeof(strErr), _T("\nCreateFile failed to create file : %s Last Error: %d"), strFileName, ::GetLastError());
			OutputDebugString(strErr);
			return;
		}
		::CloseHandle(hFile);
		memset(strErr, 0, sizeof(strErr));
		if(!csf.Open(strFileName, CFile::modeCreate|CFile::modeReadWrite|CFile::typeText|CFile::shareDenyWrite|CFile::modeNoTruncate, &e))
		{
			e.GetErrorMessage(strErr, sizeof(strErr));
			TRACE(_T("\nStill failed to open the File %s: Error Code: %s"), strFileName, strErr);
			return;
		}
	}
	csf.SeekToEnd();
	csf.WriteString(strDebugTextToLog);
	
	csf.Close();
#endif
}