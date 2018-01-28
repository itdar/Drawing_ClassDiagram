#pragma once
//CtrlPasteKey.h

#ifndef _CTRLPASTEKEY_H
#define _CTRLPASTEKEY_H

#include "KeyAction.h"
#include <afxwin.h>

class TextEdit;
class ClassDiagramForm;
class CtrlPasteKey : public KeyAction {
public:
	CtrlPasteKey();
	CtrlPasteKey(const CtrlPasteKey& source);
	virtual ~CtrlPasteKey();

	void KeyPress(TextEdit *textEdit);
	void KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc);
};

#endif // _CTRLPASTEKEY_H

