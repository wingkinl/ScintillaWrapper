#include "stdafx.h"
#include "ScintillaDemo.h"
#include "ScintillaDemoDoc.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CScintillaDemoDoc, CScintillaDoc)

BEGIN_MESSAGE_MAP(CScintillaDemoDoc, CScintillaDoc)
END_MESSAGE_MAP()

CScintillaDemoDoc::CScintillaDemoDoc()
{
}

CScintillaDemoDoc::~CScintillaDemoDoc()
{
}

#ifdef _DEBUG
void CScintillaDemoDoc::AssertValid() const
{
	CScintillaDoc::AssertValid();
}

void CScintillaDemoDoc::Dump(CDumpContext& dc) const
{
	CScintillaDoc::Dump(dc);
}
#endif //_DEBUG
