//LeftArrowKey.h

#ifndef _LEFTARROWKEY_H
#define _LEFTARROWKEY_H

#include "KeyAction.h"
#include <afxwin.h>

class TextEdit;
class ClassDiagramForm;
class LeftArrowKey : public KeyAction {
public:
	LeftArrowKey();
	LeftArrowKey(const LeftArrowKey& source);
	virtual ~LeftArrowKey();

	void KeyPress(TextEdit *textEdit);
	void KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc);
};

#endif // _LEFTARROWKEY_H