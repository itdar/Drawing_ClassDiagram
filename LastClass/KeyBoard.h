//KeyBoard.h

#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include <afxwin.h>

class KeyAction;
class TextEdit;
class ClassDiagramForm;
class KeyBoard {
public:
	KeyBoard();
	KeyBoard(const KeyBoard& source);
	~KeyBoard();

	KeyBoard& operator = (const KeyBoard& source);

	KeyAction* KeyDown(TextEdit *textEdit, UINT nChar, UINT nRepCnt, UINT nFlags);
	KeyAction* KeyDown(ClassDiagramForm *classDiagramForm, UINT nChar, UINT nRepCnt, UINT nFlags);
public:
	KeyAction *keyAction;
};

#endif // _KEYBOARD_H