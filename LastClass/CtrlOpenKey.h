//CtrlOpenKey.h

#ifndef _CTRLOPENKEY_H
#define _CTRLOPENKEY_H

#include "KeyAction.h"
#include <afxwin.h>

class TextEdit;
class ClassDiagramForm;
class CtrlOpenKey : public KeyAction {
public:
	CtrlOpenKey();
	CtrlOpenKey(const CtrlOpenKey& source);
	~CtrlOpenKey();
public:
	void KeyPress(TextEdit *textEdit);
	void KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc);
};

#endif // _CTRLOPENKEY_H