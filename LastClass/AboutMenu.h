//AboutMenu.h
#ifndef _ABOUTMENU_H
#define _ABOUTMENU_H

#include <afxwin.h>
typedef signed long int Long;

class LastClass;
class ClassDiagramForm;
class AboutMenu : public CFrameWnd {
public:
	AboutMenu(LastClass *lastClass);
private:
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
private:
	LastClass *lastClass;
};
#endif // !_ABOUTMENU_H
