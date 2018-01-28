//CtrlSaveKey.h

#ifndef _CTRLSAVEKEY_H
#define _CTRLSAVEKEY_H

#include "KeyAction.h"
#include <afxwin.h>

class TextEdit;
class ClassDiagramForm;
class CtrlSaveKey : public KeyAction {
public:
	CtrlSaveKey();
	CtrlSaveKey(const CtrlSaveKey& source);
	~CtrlSaveKey();
public:
	void KeyPress(TextEdit *textEdit);
	void KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc);
};

#endif // _CTRLSAVEKEY_H