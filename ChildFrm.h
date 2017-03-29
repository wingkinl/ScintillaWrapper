#pragma once

class CChildFrame : public CMDIChildWnd
{
public:
//Constructors / Destructors
	CChildFrame();
	virtual ~CChildFrame();

//Methods
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
//Message Handlers
	afx_msg void OnMove(int x, int y);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_DYNCREATE(CChildFrame)

	DECLARE_MESSAGE_MAP()
};
