//TextEdit.h

#ifndef _TEXTEDIT_H
#define _TEXTEDIT_H

#include <afxwin.h>
#include <imm.h>

typedef signed long int Long;

class ClassDiagramForm;
class Text;
class Figure;
class Caret;
class KeyBoard;
class HistoryText;
class TextAreaSelected;
class FontSet;
class TextEdit : public CWnd { // CWnd 상속으로 바꿔야함
public:
	TextEdit(ClassDiagramForm *classDiagramForm, Figure *figure, Long rollNameBoxIndex = -1);
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();

	afx_msg void OnKillFocus(CWnd *pNewWnd);

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);

	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg Long OnComposition(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnIMENotify(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnClose();
	Long GetFlagInsert() const;
	Long GetSelectedX() const;
	Long GetSelectedY() const;

	Figure* GetFigure() const;
	Long GetRowHeight() const;
	Long GetKoreanEnglish() const;
	Long GetFlagBuffer() const;
	CString GetCopyBuffer() const;
	Long GetCriteriaX() const;
	Long GetCriteriaWidth() const;
	Long GetCriteriaHeight() const;
public:
	ClassDiagramForm *classDiagramForm;
	Text *text;
	Caret *caret;
	KeyBoard *keyBoard;
	HistoryText *historyText;
	TextAreaSelected *textAreaSelected;
	FontSet *fontSet;
	Long flagInsert; //flag
	Long flagSelection;
	Long rowHeight; //figure에서 저장을 해줘야 하기때문에 삭제가능
	Long selectedX; //보류
	Long selectedY; //보류
	CString copyBuffer;
	Long flagBuffer; //flag
	Figure *figure;
	Long rollNameBoxIndex;
	Long fontRate;
private:
	Long koreanEnglish; //flag
	Long currentX;
	Long criteriaX;
	Long criteriaWidth;
	Long criteriaHeight;
};

inline Long TextEdit::GetFlagInsert() const {
	return this->flagInsert;
}
inline Figure* TextEdit::GetFigure() const {
	return const_cast<Figure*>(this->figure);
}
inline Long TextEdit::GetRowHeight() const {
	return this->rowHeight;
}
inline Long TextEdit::GetKoreanEnglish() const {
	return this->koreanEnglish;
}
inline Long TextEdit::GetFlagBuffer() const {
	return this->flagBuffer;
}
inline CString TextEdit::GetCopyBuffer() const {
	return this->copyBuffer;
}
inline Long TextEdit::GetSelectedX() const {
	return this->selectedX;
}
inline Long TextEdit::GetSelectedY() const {
	return this->selectedY;
}
inline Long TextEdit::GetCriteriaWidth() const {
	return this->criteriaWidth;
}
inline Long TextEdit::GetCriteriaHeight() const {
	return this->criteriaHeight;
}
inline Long TextEdit::GetCriteriaX() const {
	return this->criteriaX;
}

#endif // _TEXTEDIT_H