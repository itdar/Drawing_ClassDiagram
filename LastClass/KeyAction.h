#ifndef _KEYACTION_H
#define _KEYACTION_H

#include <afxwin.h>

class TextEdit;
class ClassDiagramForm;
class KeyAction {
public:
	KeyAction();
	virtual	~KeyAction() = 0;

	virtual void KeyPress(TextEdit *textEdit) = 0;
	virtual void KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc) = 0;
};

#endif //_KEYACTION_H