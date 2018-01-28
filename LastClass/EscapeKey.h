//EscapeKey.h

#ifndef _ESCAPEKEY_H
#define _ESCAPEKEY_H

#include "KeyAction.h"
#include <afxwin.h>

class TextEdit;
class ClassDIagrmForm;
class EscapeKey : public KeyAction {
public:
	EscapeKey();
	EscapeKey(const EscapeKey& source);
	virtual ~EscapeKey();

	void KeyPress(TextEdit *textEdit);
	void KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc);
};

#endif // _ESCAPEKEY_H