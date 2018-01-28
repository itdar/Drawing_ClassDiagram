//SupportMenu.h
#ifndef _SUPPORTMENU_H
#define _SUPPORTMENU_H

#include <afxwin.h>
typedef signed long int Long;

class LastClass;
class ClassDiagramForm;
class SupportMenu : public CFrameWnd {
public:
	SupportMenu(LastClass *lastClass);
private:
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnClose();
	afx_msg void OnNextButton();
	afx_msg void OnpreviousButton();
	afx_msg void OnOkButton();
	DECLARE_MESSAGE_MAP()
private:
	LastClass *lastClass;
	CButton *nextButton;
	CButton *previousButton;
	CButton *okButton;
	Long page;
	Long menualCount;
};
#endif // !_SUPPORTMENU_H
