//EndKey.h

#ifndef _ENDKEY_H
#define _ENDKEY_H

#include "KeyAction.h"
#include <afxwin.h>

class TextEdit;
class ClassDiagramForm;
class EndKey : public KeyAction {
public:
	EndKey();
	EndKey(const EndKey& source);
	virtual ~EndKey();

	void KeyPress(TextEdit *textEdit);
	void KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc);
};

#endif // _ENDKEY_H