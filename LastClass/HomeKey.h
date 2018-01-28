//HomeKey.h

#ifndef _HOMEKEY_H
#define _HOMEKEY_H

#include "KeyAction.h"
#include <afxwin.h>

class TextEdit;
class CLassDiagramForam;
class HomeKey : public KeyAction {
public:
	HomeKey();
	HomeKey(const HomeKey& source);
	virtual ~HomeKey();

	void KeyPress(TextEdit *textEdit);
	void KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc);
};

#endif // _HOMEKEY_H