//BackSpaceKey.h

#ifndef _BACKSPACEKEY_H
#define _BACKSPACEKEY_H

#include "KeyAction.h"
#include <afxwin.h>

class TextEdit;
class ClassDiagramForm;
class BackSpaceKey : public KeyAction {
public:
	BackSpaceKey();
	BackSpaceKey(const BackSpaceKey& source);
	virtual ~BackSpaceKey();

	void KeyPress(TextEdit *textEdit);
	void KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc);
};

#endif // _BACKSPACEKEY_H