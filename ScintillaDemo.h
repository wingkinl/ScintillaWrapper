#pragma once

#include "resource.h"       // main symbols

class CScintillaDemoApp : public CWinApp
{
public:
//Constructors / Destructors
  CScintillaDemoApp();

//Methods
  BOOL InitInstance() override;
  int ExitInstance() override;
  HMODULE LoadLibraryFromApplicationDirectory(LPCTSTR lpFileName);

//Message handlers
  afx_msg void OnAppAbout();

  DECLARE_MESSAGE_MAP()

//Member variables
  HINSTANCE m_hSciDLL;
};
