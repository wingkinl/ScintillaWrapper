#include "stdafx.h"
#include "ScintillaDemo.h"
#include "ChildFrm.h"
#include "ScintillaDemoDoc.h"
#include "ScintillaDemoView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#pragma warning(suppress: 26409 26433 26440)
IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

#pragma warning(suppress: 26433 26440)
BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
  ON_WM_MOVE()
  ON_WM_SIZE()
END_MESSAGE_MAP()

#pragma warning(suppress: 26434)
void CChildFrame::OnMove(int x, int y)
{
  //Let the base class do its thing
  __super::OnMove(x, y);

#pragma warning(suppress: 26466)
  CScintillaDemoView* pView = static_cast<CScintillaDemoView*>(GetActiveView());
  if (pView != nullptr)
  {
    if (pView->IsKindOf(RUNTIME_CLASS(CScintillaDemoView)))
    {
      CScintillaCtrl& rCtrl = pView->GetCtrl();

      //Cancel any outstanding call tip
      if (rCtrl.CallTipActive())
        rCtrl.CallTipCancel();
    }
  }
}

#pragma warning(suppress: 26434)
void CChildFrame::OnSize(UINT nType, int cx, int cy) 
{
  //Let the base class do its thing
  CMDIChildWnd::OnSize(nType, cx, cy);
  
#pragma warning(suppress: 26466)
  CScintillaDemoView* pView = static_cast<CScintillaDemoView*>(GetActiveView());
  if (pView != nullptr)
  {
    if (pView->IsKindOf(RUNTIME_CLASS(CScintillaDemoView)))
    {
      CScintillaCtrl& rCtrl = pView->GetCtrl();

      //Cancel any outstanding call tip
      if (rCtrl.CallTipActive())
        rCtrl.CallTipCancel();
    }
  }
}
