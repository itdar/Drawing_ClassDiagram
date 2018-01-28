//LastClass.h

#ifndef _LASTCLASS_H
#define _LASTCLASS_H

#include <afxwin.h>
using namespace std;

typedef signed long int Long;

class StatusBar;
class ToolBar;
class Menu;
class ClassDiagramForm;
class ToolBar;
class StatusBar;
class PrintPreview;
class LastClass : public CFrameWnd {
public:
	LastClass();
public:
	ClassDiagramForm *classDiagramForm;
	Menu *menu;
	ToolBar *toolBar;
	StatusBar *statusBar;
	PrintPreview *printPreview;
	Long one = 0;
public:
	afx_msg void OnClose();
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMyMenu(UINT parm_control_id);
	afx_msg void OnMyToolBar(UINT parm_control_id);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR *lpMMI);
	DECLARE_MESSAGE_MAP()
};

#endif // _LASTCLASS_H