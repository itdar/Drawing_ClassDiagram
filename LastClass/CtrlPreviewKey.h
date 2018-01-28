//CtrlPreviewKey.h

#ifndef _CTRLPREVIEWKEY_H
#define _CTRLPREVIEWKEY_H

#include "KeyAction.h"
#include <afxwin.h>

class TextEdit;
class ClassDiagramForm;
class CtrlPreviewKey : public KeyAction {
public:
	CtrlPreviewKey();
	CtrlPreviewKey(const CtrlPreviewKey& source);
	~CtrlPreviewKey();
public:
	void KeyPress(TextEdit *textEdit);
	void KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc);
};

#endif // _CTRLPREVIEWKEY_H