//MinusKey.h

#ifndef _MINUSKEY_H
#define _MINUSKEY_H

#include "KeyAction.h"
#include <afxwin.h>

class TextEdit;
class ClassDiagramForm;
class  MinusKey : public KeyAction {
public:
	MinusKey();
	MinusKey(const MinusKey& source);
	virtual ~MinusKey();

	void KeyPress(TextEdit *textEdit);
	void KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc);
};

#endif // _LEFTARROWKEY_H