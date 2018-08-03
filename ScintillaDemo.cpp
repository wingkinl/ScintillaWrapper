#include "stdafx.h"
#include "ScintillaDemo.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "ScintillaDemoDoc.h"
#include "ScintillaDemoView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma warning(suppress: 26440 26433)
BEGIN_MESSAGE_MAP(CScintillaDemoApp, CWinApp)
  ON_COMMAND(ID_APP_ABOUT, &CScintillaDemoApp::OnAppAbout)
  ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
  ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
  ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

#pragma warning(suppress: 26426)
CScintillaDemoApp theApp;


#pragma warning(suppress: 26439)
CScintillaDemoApp::CScintillaDemoApp() : m_hSciDLL(nullptr)
{
}

HMODULE CScintillaDemoApp::LoadLibraryFromApplicationDirectory(LPCTSTR lpFileName)
{
  //Get the Application diretory
  CString sFullPath;
  const int nGMFN = GetModuleFileName(nullptr, sFullPath.GetBuffer(_MAX_PATH), _MAX_PATH);
  sFullPath.ReleaseBuffer();
  if (nGMFN == 0)
    return nullptr;

  //Form the new path
  CString sDrive;
  CString sDir;
  _tsplitpath_s(sFullPath, sDrive.GetBuffer(_MAX_DRIVE), _MAX_DRIVE, sDir.GetBuffer(_MAX_DIR), _MAX_DIR, nullptr, 0, nullptr, 0);
  sDir.ReleaseBuffer();
  sDrive.ReleaseBuffer();
  CString sFname;
  CString sExt;
  _tsplitpath_s(lpFileName, nullptr, 0, nullptr, 0, sFname.GetBuffer(_MAX_FNAME), _MAX_FNAME, sExt.GetBuffer(_MAX_EXT), _MAX_EXT);
  sExt.ReleaseBuffer();
  sFname.ReleaseBuffer();
  _tmakepath_s(sFullPath.GetBuffer(_MAX_PATH), _MAX_PATH, sDrive, sDir, sFname, sExt);
  sFullPath.ReleaseBuffer();

  //Delegate to LoadLibrary
  return LoadLibrary(sFullPath);
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
#pragma warning(suppress: 26400 26409)
  CMultiDocTemplate* pDocTemplate = new CMultiDocTemplate(IDR_SCINTITYPE,
    RUNTIME_CLASS(CScintillaDemoDoc),
    RUNTIME_CLASS(CChildFrame), // custom MDI child frame
    RUNTIME_CLASS(CScintillaDemoView));
  AddDocTemplate(pDocTemplate);

  //create main MDI Frame window
#pragma warning(suppress: 26400 26409)
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
  {
    FreeLibrary(m_hSciDLL);
    m_hSciDLL = nullptr;
  }

  //Let the base class do its thing
  return __super::ExitInstance();
}


class CAboutDlg : public CDialog
{
public:
  CAboutDlg();

  enum { IDD = IDD_ABOUTBOX };

protected:
  virtual void DoDataExchange(CDataExchange* pDX);

  DECLARE_MESSAGE_MAP()
};

#pragma warning(suppress: 26439)
CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

#pragma warning(suppress: 26433)
void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
  //Let the base class do its thing
  CDialog::DoDataExchange(pDX);
}

#pragma warning(suppress: 26440 26433)
BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

void CScintillaDemoApp::OnAppAbout()
{
  CAboutDlg aboutDlg;
  aboutDlg.DoModal();
}
