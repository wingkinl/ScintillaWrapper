#pragma once

#include "resource.h"       // main symbols

class CScintillaDemoApp : public CWinApp
{
public:
  CScintillaDemoApp();

  virtual BOOL InitInstance();
  virtual int ExitInstance();
  HMODULE LoadLibraryFromApplicationDirectory(LPCTSTR lpFileName);

  afx_msg void OnAppAbout();

  DECLARE_MESSAGE_MAP()

  HINSTANCE m_hSciDLL;
};
