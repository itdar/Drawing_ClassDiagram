//CtrlPrintKey.h

#ifndef _CTRLPRINTKEY_H
#define _CTRLPRINTKEY_H

#include "KeyAction.h"
#include <afxwin.h>

class TextEdit;
class ClassDiagramForm;
class CtrlPrintKey : public KeyAction {
public:
	CtrlPrintKey();
	CtrlPrintKey(const CtrlPrintKey& source);
	~CtrlPrintKey();
public:
	void KeyPress(TextEdit *textEdit);
	void KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc);
};

#endif // _CTRLPRINTKEY_H