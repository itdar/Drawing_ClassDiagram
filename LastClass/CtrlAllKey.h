//CtrlAllKey.h

#ifndef _CTRLALLKEY_H
#define _CTRLALLKEY_H

#include "KeyAction.h"
#include <afxwin.h>

class TextEdit;
class ClassDiagramForm;
class CtrlAllKey : public KeyAction {
public:
	CtrlAllKey();
	CtrlAllKey(const CtrlAllKey& source);
	virtual ~CtrlAllKey();

	void KeyPress(TextEdit *textEdit);
	void KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc);
};

#endif //_CTRLALLKEY_H