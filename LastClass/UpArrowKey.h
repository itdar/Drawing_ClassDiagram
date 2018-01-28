//UpArrowKey.h

#ifndef _UPARROWKEY_H
#define _UPARROWKEY_H

#include "KeyAction.h"
#include <afxwin.h>

class TextEdit;
class ClassDiagramForm;
class UpArrowKey : public KeyAction {
public:
	UpArrowKey();
	UpArrowKey(const UpArrowKey& source);
	virtual ~UpArrowKey();

	void KeyPress(TextEdit *textEdit);
	void KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc);
};

#endif // _UPARROWKEY_H