#pragma once

#include "ScintillaDocView.h"

class CScintillaDemoDoc : public CScintillaDoc
{
protected: //create from serialization only
	CScintillaDemoDoc();
	DECLARE_DYNCREATE(CScintillaDemoDoc)

public:
	virtual ~CScintillaDemoDoc();
	
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DECLARE_MESSAGE_MAP()
};
