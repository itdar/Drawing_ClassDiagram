//CtrlCutKey.h

#ifndef _CTRLCUTKEY_H
#define _CTRLCUTKEY_H

#include "KeyAction.h"
#include <afxwin.h>

class TextEdit;
class ClassDiagramForm;
class CtrlCutKey : public KeyAction {
public:
	CtrlCutKey();
	CtrlCutKey(const CtrlCutKey& source);
	virtual ~CtrlCutKey();

	void KeyPress(TextEdit *textEdit);
	void KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc);
};

#endif // _CTRLCUTKEY_H

