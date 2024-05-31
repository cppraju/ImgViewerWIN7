#pragma once



// CCaptionPanelBar



class CCaptionPanelBar : public CDialogBar
{
	DECLARE_DYNAMIC(CCaptionPanelBar)

// Dialog Data
	//{{AFX_DATA(CTestDlgBar)
	enum { IDD = IDD_DIALOGBAR_MAIN };
	int		m_rad;
	//}}AFX_DATA
public:
	CCaptionPanelBar();
	virtual ~CCaptionPanelBar();
	//overrides
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL Create(CWnd* pParentWnd, UINT nIDTemplate, UINT nStyle, UINT nID);
	virtual BOOL Create(CWnd *pparentWnd, LPCTSTR lpszTemplateName, UINT nStyle, UINT nID);
	virtual BOOL OnInitDialog();

	CRect brec;
	CString csImgFileName;
	// path of the selected image file
	CString csImgFilePath;
	// extension of the image file
	CString csImgExt;
	//folder dlg path
	CString csFolderDlgPath;
	bool m_bLBDown;
	bool m_bHTCLIENT;
	CPoint m_OldPoint;
	CBrush m_hbrDlg;
	CBitmap m_Brbm;
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonDir();
	afx_msg void OnUpdateButtonDir(CCmdUI *pCmdUI);
	afx_msg void OnBnClickedAlgo1();
	afx_msg void OnUpdateButtonAlgo1(CCmdUI *pCmdUI);
	afx_msg void OnBnClickedButtonFile();
	afx_msg void OnUpdateButtonFile(CCmdUI *pCmdUI);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};


