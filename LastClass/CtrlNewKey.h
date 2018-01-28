//CtrlNewKey.h

#ifndef _CTRLNEWKEY_H
#define _CTRLNEWKEY_H

#include "KeyAction.h"
#include <afxwin.h>

class TextEdit;
class ClassDiagramForm;
class CtrlNewKey : public KeyAction {
public:
	CtrlNewKey();
	CtrlNewKey(const CtrlNewKey& source);
	~CtrlNewKey();
public:
	void KeyPress(TextEdit *textEdit);
	void KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc);
};

#endif // _CTRLNEWKEY_H