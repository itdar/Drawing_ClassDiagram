//F1HelpKey.h

#ifndef _F1HELPKEY_H
#define _F1HELPKEY_H

#include "KeyAction.h"
#include <afxwin.h>

class TextEdit;
class ClassDiagramForm;
class F1HelpKey : public KeyAction {
public:
	F1HelpKey();
	F1HelpKey(const F1HelpKey& source);
	~F1HelpKey();
public:
	void KeyPress(TextEdit *textEdit);
	void KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc);
};

#endif // _F1HELPKEY_H