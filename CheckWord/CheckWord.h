// CheckWord.h : main header file for the CHECKWORD application
//

#if !defined(AFX_CHECKWORD_H__AF4A1505_A498_49CE_B037_03D2B05CC003__INCLUDED_)
#define AFX_CHECKWORD_H__AF4A1505_A498_49CE_B037_03D2B05CC003__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCheckWordApp:
// See CheckWord.cpp for the implementation of this class
//

class CCheckWordApp : public CWinApp
{
public:
	CCheckWordApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCheckWordApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCheckWordApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHECKWORD_H__AF4A1505_A498_49CE_B037_03D2B05CC003__INCLUDED_)
