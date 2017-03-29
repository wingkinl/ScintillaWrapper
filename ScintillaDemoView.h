#pragma once

#include "ScintillaDocView.h"

class CScintillaDemoView : public CScintillaView
{
protected: //create from serialization only
  CScintillaDemoView();
  DECLARE_DYNCREATE(CScintillaDemoView)

//Attributes
public:
  CScintillaDemoDoc* GetDocument();

  virtual void OnDraw(CDC* pDC);  //overridden to draw this view
  virtual void OnInitialUpdate();

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

protected:
  afx_msg void OnOptionsAddmarker();
  afx_msg void OnOptionsDeletemarker();
  afx_msg void OnUpdateOptionsDeletemarker(CCmdUI* pCmdUI);
  afx_msg void OnOptionsFindNextmarker();
  afx_msg void OnOptionsFindPrevmarker();
  afx_msg void OnOptionsFoldMargin();
  afx_msg void OnOptionsSelectionMargin();
  afx_msg void OnUpdateOptionsSelectionMargin(CCmdUI* pCmdUI);
  afx_msg void OnOptionsViewLinenumbers();
  afx_msg void OnUpdateOptionsViewLinenumbers(CCmdUI* pCmdUI);
  afx_msg void OnUpdateOptionsAddmarker(CCmdUI* pCmdUI);
  afx_msg void OnUpdateOptionsFoldMargin(CCmdUI* pCmdUI);
  afx_msg void OnUpdateLine(CCmdUI* pCmdUI);
  afx_msg void OnUpdateStyle(CCmdUI* pCmdUI);
  afx_msg void OnUpdateFold(CCmdUI* pCmdUI);
  afx_msg void OnUpdateInsert(CCmdUI* pCmdUI);
  afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);

  DECLARE_MESSAGE_MAP()
    
  virtual void OnCharAdded(_Inout_ SCNotification* pSCNotification);
  virtual void OnDwellStart(_Inout_ SCNotification* pSCNotification);
  virtual void OnDwellEnd(_Inout_ SCNotification* pSCNotification);
  virtual void OnModifyAttemptRO(_Inout_ SCNotification* pSCNotification);
  virtual void OnModified(_Inout_ SCNotification* pSCNotification);

  void SetAStyle(int style, COLORREF fore, COLORREF back=RGB(0xff, 0xff, 0xff), int size=-1, const char *face=0);
  void DefineMarker(int marker, int markerType, COLORREF fore, COLORREF back);
};

#ifndef _DEBUG  //debug version in ScintillaDemoView.cpp
inline CScintillaDemoDoc* CScintillaDemoView::GetDocument()
{ 
  return static_cast<CScintillaDemoDoc*>(m_pDocument); 
}
#endif
