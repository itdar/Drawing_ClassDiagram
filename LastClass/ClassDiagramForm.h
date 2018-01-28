//ClassDiagramForm.h

#ifndef _CLASSDIAGRAM_H
#define _CLASSDIAGRAM_H

#include <afxwin.h>
#include <string>

typedef signed long int Long;

extern Long MemoGab;
extern Long GabX;
extern Long GabY;
extern Long CaretWidth;

class Diagram; //전방선언
class TextEdit;
class Selection;
class MouseLButton;
class KeyBoard;
class HistoryGraphic;
class Menu;
class Scroll;
class LastClass;
class ClassDiagramFormMenu;
class ClassDiagramForm : public CWnd { //CFrameWnd 에 상속관계 표기
public:
	LastClass *lastClass;
	Diagram *diagram;
	TextEdit *textEdit;
	Selection *selection;
	MouseLButton *mouseLButton;
	KeyBoard *keyBoard;
	HistoryGraphic *historyGraphic;
	Scroll *scroll;
	Selection *copyBuffer;
	ClassDiagramFormMenu *classDiagramFormMenu;
	Long isCut;
	Long capsLockFlag;
	Long numLockFlag;
	Long zoomRate;
	Long preZoom;
	Long isDown;
	Long startX_;
	Long startY_;
	Long currentX_;
	Long currentY_;
	Long currentX_2;
	Long currentY_2;
	Long thirty;
	Long seventeen;
	Long widthGab;
	Long heightGab;
	Long firstDrag;
public:
	ClassDiagramForm(LastClass *lastClass);
public:
	afx_msg void OnClose();
public:
	Long Load();
	Long Save();
	CString fileName;
public:

	Long GetStartX() const;
	Long GetStartY() const;
	Long GetCurrentX() const;
	Long GetCurrentY() const;
public:
	void SetMemoGab(Long memoGab) const;
	void SetGabX(Long gabX) const;
	void SetGabY(Long gabY) const;
	void SetCaretWidth(Long caretWidth) const;
	CString SetFileName(CString fileName) ;
	CString GetFileName() const;
private:
	Long startX;
	Long startY;
	Long currentX;
	Long currentY;
	bool isDblclk;
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMyMenu(UINT parm_control_id);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar); 
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR *lpMMI);
	DECLARE_MESSAGE_MAP()
};
Long inline ClassDiagramForm::GetStartX() const {
	return this->startX;
}
Long inline ClassDiagramForm::GetStartY() const {
	return this->startY;
}
Long inline ClassDiagramForm::GetCurrentX() const {
	return this->currentX;
}
Long inline ClassDiagramForm::GetCurrentY() const {
	return this->currentY;
}

void inline ClassDiagramForm::SetMemoGab(Long memoGab) const {
	if (MemoGab == 0) {
		MemoGab = 1;
	}
	else {
		MemoGab = memoGab;
	}
}
void inline ClassDiagramForm::SetGabX(Long gabX) const {
	if (GabX == 0) {
		GabX = 1;
	}
	else {
		GabX = gabX;
	}
}
void inline ClassDiagramForm::SetGabY(Long gabY) const {
	if (gabY == 0) {
		GabY = 0;
	}
	else {
		GabY = gabY;
	}
}
void inline ClassDiagramForm::SetCaretWidth(Long caretWidth) const {
	if (caretWidth == 0) {
		CaretWidth = 1;
	}
	else {
		CaretWidth = caretWidth;
	}
}
CString inline ClassDiagramForm::GetFileName()const {
	return this->fileName;
}
#endif // _CLASSDIAGRAM_H