//EnterKey.h

#ifndef _ENTERKEY_H
#define _ENTERKEY_H

#include "KeyAction.h"
#include <afxwin.h>

class TextEdit;
class ClassDIagrmForm;
class EnterKey : public KeyAction {
public:
	EnterKey();
	EnterKey(const EnterKey& source);
	virtual ~EnterKey();

	void KeyPress(TextEdit *textEdit);
	void KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc);
};

#endif // _ENTERKEY_H