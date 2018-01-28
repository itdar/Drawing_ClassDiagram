//RightArrowKey.h

#ifndef _RIGHTARROWKEY_H
#define _RIGHTARROWKEY_H

#include "KeyAction.h"
#include <afxwin.h>

class TextEdit;
class ClassDiagramForm;
class RightArrowKey : public KeyAction {
public:
	RightArrowKey();
	RightArrowKey(const RightArrowKey& source);
	virtual ~RightArrowKey();

	void KeyPress(TextEdit *textEdit);
	void KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc);
};

#endif // _RIGHTARROWKEY_H