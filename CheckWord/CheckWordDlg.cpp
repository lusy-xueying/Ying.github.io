// CheckWordDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CheckWord.h"
#include "CheckWordDlg.h"


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <cctype>
using namespace std;
#include <windows.h> 
#include <afxpriv.h>
 string  strWord ;
void LCSLength(int m,int n,char *x,char *y,int **c);  
void LCS(int i,int j,char *x,int **c);  

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCheckWordDlg dialog

CCheckWordDlg::CCheckWordDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCheckWordDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCheckWordDlg)
	m_btFileFirst = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCheckWordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCheckWordDlg)
	DDX_Control(pDX, IDC_EDIT_SECONDRE, m_cEditRepeatSecond);
	DDX_Control(pDX, IDC_EDIT_FIRST_RE, m_cEditRepeatFirst);
	DDX_Control(pDX, IDC_BUTTON_FILE_FIRST, m_EditRepeatFirst);
	DDX_Control(pDX, IDC_RICHEDIT_FIRST, m_RichFirst);
	DDX_Control(pDX, IDC_RICHEDIT_SECOND, m_RichSecond);
	DDX_Control(pDX, IDC_EDIT_FILE_SECOND, m_EditFileSecond);
	DDX_Control(pDX, IDC_EDIT_FILE_FIRST, m_editFileFirst);
	DDX_Control(pDX, IDC_BUTTON_FILE_SECOND, m_btFileSecond);
	DDX_Text(pDX, IDC_EDIT_FILE_FIRST, m_btFileFirst);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCheckWordDlg, CDialog)
	//{{AFX_MSG_MAP(CCheckWordDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_FILE_FIRST, OnButtonFileFirst)
	ON_BN_CLICKED(IDC_BUTTON_FILE_SECOND, On2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCheckWordDlg message handlers

BOOL CCheckWordDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCheckWordDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCheckWordDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCheckWordDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

string readFileIntolib(char * filename)

{
	ifstream ifile(filename);
	ostringstream buf;
	char ch;
	
	while(buf&&ifile.get(ch))
		buf.put(ch);
	//返回与流对象buf关联的字符串
	return buf.str();
}

void CCheckWordDlg::SetEditColor(CRichEditCtrl &editCtrl,int nPosStart,int nPosEnd)
{
	CHARFORMAT cf;

	ZeroMemory(&cf, sizeof(CHARFORMAT));

	cf.cbSize = sizeof(CHARFORMAT);

	cf.dwMask|=CFM_BOLD;

	cf.dwEffects|=CFE_BOLD; //粗体，取消用cf.dwEffects&=~CFE_BOLD;

	cf.dwMask|=CFM_ITALIC;

	cf.dwEffects|=CFE_ITALIC; //斜体，取消用cf.dwEffects&=~CFE_ITALIC;

	cf.dwMask|=CFM_UNDERLINE;

	cf.dwEffects|=CFE_UNDERLINE; //斜体，取消用cf.dwEffects&=~CFE_UNDERLINE;

	cf.dwMask|=CFM_COLOR;

	cf.crTextColor = RGB(255,0,255); //设置颜色

	cf.dwMask|=CFM_SIZE;

	cf.yHeight =400; //设置高度

	cf.dwMask|=CFM_FACE;

	strcpy(cf.szFaceName ,_T("隶书")); //设置字体

	//m_edit.GetSel(start, end);//获取选中文字的起始结束位置

	editCtrl.SetSel(nPosStart, nPosEnd);//设置文字位置

	editCtrl.SetWordCharFormat(cf);
}
void CCheckWordDlg::OnOK() 
{
	USES_CONVERSION;
	strWord ="";
	CString strFirstFile;
	CString strSecondFile;
	string  strFileData;
	string  strFileDataSecond;
	CString cstrFirstFile;
	CString cstrSecondFile;
	//获取第一个文件内容
	m_editFileFirst.GetWindowText(strFirstFile);
	//获取第二个文件内容
	m_EditFileSecond.GetWindowText(strSecondFile);
	
	m_RichFirst.GetWindowText(cstrFirstFile);
	m_RichSecond.GetWindowText(cstrSecondFile);
	
	strFileData       = " " ;
	strFileDataSecond = " " ;
	strFileData       += cstrFirstFile.GetBuffer(cstrFirstFile.GetLength());
	strFileDataSecond += cstrSecondFile.GetBuffer(cstrSecondFile.GetLength());
	CString str;

	int nFirstFileLen  = strFileData.size();
	int nSecondFileLen = strFileDataSecond.size();
	
	int **c			   = new int *[nFirstFileLen+1];  
	for(int i=0;i<=nFirstFileLen;i++)    
	{    
		c[i] = new int[nSecondFileLen+1];  
		*c[i] = 0;
	}  
	
	//compute longest data length

	LCSLength(nFirstFileLen,nSecondFileLen,(char*)strFileData.c_str(),(char*)strFileDataSecond.c_str(),c);  
	
	LCS(nFirstFileLen,nSecondFileLen,(char*)strFileData.c_str(),c);

	
	for (int n=0; n<strWord.size();n++)
	{
		int nIndex = strFileData.find(strWord[n]);
		SetEditColor(m_RichFirst,nIndex-1,nIndex);	
	}
	for (int m=0; m<strWord.size();m++)
	{
		int nIndex = strFileDataSecond.find(strWord[m]);
		SetEditColor(m_RichSecond,nIndex-1,nIndex);	
	}


	CString  strFirstRepeat;
	CString   strSeconRepeat;
	CString p;

	int nlenFirst  = (float)strWord.size()/(strFileData.size()-1)*100;
	int nlenSecond = (float)strWord.size()/(strFileDataSecond.size()-1)*100;

	strFirstRepeat.Format("%d",nlenFirst);
	strSeconRepeat.Format("%d",nlenSecond);
	m_cEditRepeatFirst.SetWindowText(strFirstRepeat);
	m_cEditRepeatSecond.SetWindowText(strSeconRepeat);
	delete []c;
	AfxMessageBox((CString)strWord.c_str());
    p.Format("%d",strWord.size());
	AfxMessageBox(p);
}

//从文件读入到string里

void LCSLength(int m,int n,char *x,char *y,int **c)  
{  
    int i,j;  
	
    for(i=1; i<=m; i++)  
        c[i][0] = 0;  
    for(i=1; i<=n; i++)  
        c[0][i] = 0;  
	
    for(i=1; i<=m; i++)  
    {  
        for(j=1; j<=n; j++)  
        {  
            if(x[i]==y[j])  
            {  
                c[i][j]=c[i-1][j-1]+1;  
				
            }  
            else if(c[i-1][j]>=c[i][j-1])  
            {  
                c[i][j]=c[i-1][j];  
				
			}  
            else  
            {  
				c[i][j]=c[i][j-1];
				
            }  
        }  
    }  
}  

void LCS(int i,int j,char *x,int **c)  
{  
    if(i==0 || j==0)  
    {  
        return;  
    }  
    if(c[i][j]==c[i-1][j-1]+1)  
    {  
        LCS(i-1,j-1,x,c); 
		string str ;
		str += x[i];
		strWord += str.c_str();
	 
    }  
    else if(c[i-1][j]>=c[i][j-1])
    {  
        LCS(i-1,j,x,c);  
    }  
    else  
    {  
        LCS(i,j-1,x,c);  
    }  
}  



//选择文件
CString SelectFile()
{
	CString strFile = _T("");
	CFileDialog    dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("Describe Files (*.txt)|*.txt|All Files (*.*)|*.*||"), NULL);
	if (dlgFile.DoModal())
	 {
		 strFile = dlgFile.GetPathName();
	 }
	return strFile;
}
void CCheckWordDlg::OnButtonFileFirst() 
{
	CString  strFileName = SelectFile();
	
	string strFirstfile  = "";
	//read file 
	strFirstfile  += readFileIntolib((LPSTR)(LPCTSTR)strFileName);
	//存放路径
	m_editFileFirst.SetWindowText(strFileName);
	//存放第一个文件内容
	m_RichFirst.SetWindowText((LPCTSTR)strFirstfile.c_str());
}

void CCheckWordDlg::On2() 
{
		CString  strFileName = SelectFile();
		
		string strSecondFILE  = "";
		//read file 
		strSecondFILE  += readFileIntolib((LPSTR)(LPCTSTR)strFileName);
		//存放路径
		m_EditFileSecond.SetWindowText(strFileName);
		//存放第一个文件内容
		m_RichSecond.SetWindowText((LPCTSTR)strSecondFILE.c_str());
}
