//CtrlEnterKey.h

#ifndef _CTRLENTERKEY_H
#define _CTRLENTERKEY_H

#include "KeyAction.h"
#include <afxwin.h>

class TextEdit;
class ClassDiagramForm;
class CtrlEnterKey : public KeyAction {
public:
	CtrlEnterKey();
	CtrlEnterKey(const CtrlEnterKey& source);
	virtual ~CtrlEnterKey();

	void KeyPress(TextEdit *textEdit);
	void KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc);
};


#endif // _CTRLENTERKEY_H