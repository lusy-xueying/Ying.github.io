// CheckWordDlg.h : header file
//

#if !defined(AFX_CHECKWORDDLG_H__CCB53A03_6826_4B12_BA8F_B9AEDF6A97C3__INCLUDED_)
#define AFX_CHECKWORDDLG_H__CCB53A03_6826_4B12_BA8F_B9AEDF6A97C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCheckWordDlg dialog

class CCheckWordDlg : public CDialog
{
// Construction
public:
	CCheckWordDlg(CWnd* pParent = NULL);	// standard constructor
	void SetEditColor(CRichEditCtrl& editCtrl,int nPosStart,int nPosEnd);
// Dialog Data
	//{{AFX_DATA(CCheckWordDlg)
	enum { IDD = IDD_CHECKWORD_DIALOG };
	CEdit	m_cEditRepeatSecond;
	CEdit	m_cEditRepeatFirst;
	CButton	m_EditRepeatFirst;
	CRichEditCtrl	m_RichFirst;
	CRichEditCtrl	m_RichSecond;
	CEdit	m_EditFileSecond;
	CEdit	m_editFileFirst;
	CButton	m_btFileSecond;
	CString	m_btFileFirst;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCheckWordDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCheckWordDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnButtonFileFirst();
	afx_msg void On2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHECKWORDDLG_H__CCB53A03_6826_4B12_BA8F_B9AEDF6A97C3__INCLUDED_)
