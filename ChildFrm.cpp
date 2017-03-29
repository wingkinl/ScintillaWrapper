#include "stdafx.h"
#include "ScintillaDemo.h"
#include "ChildFrm.h"
#include "ScintillaDemoDoc.h"
#include "ScintillaDemoView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
  ON_WM_MOVE()
  ON_WM_SIZE()
END_MESSAGE_MAP()


CChildFrame::CChildFrame()
{
}

CChildFrame::~CChildFrame()
{
}

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
  CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
  CMDIChildWnd::Dump(dc);
}
#endif //_DEBUG

void CChildFrame::OnMove(int x, int y) 
{
  //Let the base class do its thing
  CMDIChildWnd::OnMove(x, y);
  
  CScintillaDemoView* pView = static_cast<CScintillaDemoView*>(GetActiveView());
  if (pView)
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

void CChildFrame::OnSize(UINT nType, int cx, int cy) 
{
  //Let the base class do its thing
  CMDIChildWnd::OnSize(nType, cx, cy);
  
  CScintillaDemoView* pView = static_cast<CScintillaDemoView*>(GetActiveView());
  if (pView)
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
