//CtrlCopyKey.h

#ifndef _CTRLCOPYKEY_H
#define _CTRLCOPYKEY_H

#include "KeyAction.h"
#include <afxwin.h>

class TextEdit;
class CLassDIagrmForm;
class CtrlCopyKey : public KeyAction {
public:
	CtrlCopyKey();
	CtrlCopyKey(const CtrlCopyKey& source);
	virtual ~CtrlCopyKey();

	void KeyPress(TextEdit *textEdit);
	void KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc);
};

#endif // _CTRLCOPYKEY_H