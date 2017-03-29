#include "stdafx.h"
#include "ScintillaDemo.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "ScintillaDemoDoc.h"
#include "ScintillaDemoView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CScintillaDemoApp, CWinApp)
  ON_COMMAND(ID_APP_ABOUT, &CScintillaDemoApp::OnAppAbout)
  ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
  ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
  ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

CScintillaDemoApp theApp;


CScintillaDemoApp::CScintillaDemoApp()
{
}

HMODULE CScintillaDemoApp::LoadLibraryFromApplicationDirectory(LPCTSTR lpFileName)
{
  //Get the Application diretory
  TCHAR szFullPath[_MAX_PATH];
  szFullPath[0] = _T('\0');
  if (GetModuleFileName(nullptr, szFullPath, _countof(szFullPath)) == 0)
    return nullptr;

  //Form the new path
  TCHAR szDrive[_MAX_DRIVE];
  szDrive[0] = _T('\0');
  TCHAR szDir[_MAX_DIR];
  szDir[0] = _T('\0');
  _tsplitpath_s(szFullPath, szDrive, sizeof(szDrive)/sizeof(TCHAR), szDir, sizeof(szDir)/sizeof(TCHAR), nullptr, 0, nullptr, 0);
   TCHAR szFname[_MAX_FNAME];
   szFname[0] = _T('\0');
   TCHAR szExt[_MAX_EXT];
   szExt[0] = _T('\0');
  _tsplitpath_s(lpFileName, nullptr, 0, nullptr, 0, szFname, sizeof(szFname)/sizeof(TCHAR), szExt, sizeof(szExt)/sizeof(TCHAR));
  _tmakepath_s(szFullPath, sizeof(szFullPath)/sizeof(TCHAR), szDrive, szDir, szFname, szExt);

  //Delegate to LoadLibrary    
  return LoadLibrary(szFullPath);
}

BOOL CScintillaDemoApp::InitInstance()
{
  //Load the scintilla dll
  m_hSciDLL = LoadLibraryFromApplicationDirectory(_T("SciLexer.dll"));
  if (m_hSciDLL == nullptr)
  { 
    AfxMessageBox(_T("Scintilla DLL is not installed, Please download the SciTE editor and copy the SciLexer.dll into this application's directory"));
    return FALSE;
  }

  SetRegistryKey(_T("PJ Naughter"));

  LoadStdProfileSettings();  // Load standard INI file options (including MRU)

  //Register the application's document templates.  Document templates
  //serve as the connection between documents, frame windows and views.
  CMultiDocTemplate* pDocTemplate = new CMultiDocTemplate(IDR_SCINTITYPE,
    RUNTIME_CLASS(CScintillaDemoDoc),
    RUNTIME_CLASS(CChildFrame), // custom MDI child frame
    RUNTIME_CLASS(CScintillaDemoView));
  AddDocTemplate(pDocTemplate);

  //create main MDI Frame window
  CMainFrame* pMainFrame = new CMainFrame;
  if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
    return FALSE;
  m_pMainWnd = pMainFrame;

  //Parse command line for standard shell commands, DDE, file open
  CCommandLineInfo cmdInfo;
  ParseCommandLine(cmdInfo);

  //Dispatch commands specified on the command line
  if (!ProcessShellCommand(cmdInfo))
    return FALSE;

  //The main window has been initialized, so show and update it.
  pMainFrame->ShowWindow(m_nCmdShow);
  pMainFrame->UpdateWindow();

  //Enable drag/drop open
  m_pMainWnd->DragAcceptFiles();

  return TRUE;
}

int CScintillaDemoApp::ExitInstance() 
{
  //Free up the Scintilla DLL
  if (m_hSciDLL)
    FreeLibrary(m_hSciDLL);
  
  return CWinApp::ExitInstance();
}


class CAboutDlg : public CDialog
{
public:
  CAboutDlg();

  enum { IDD = IDD_ABOUTBOX };

protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
  //Let the base class do its thing
  CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

void CScintillaDemoApp::OnAppAbout()
{
  CAboutDlg aboutDlg;
  aboutDlg.DoModal();
}
