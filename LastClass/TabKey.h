//TabKey.h

#ifndef _TABKEY_H
#define _TABKEY_H

#include "KeyAction.h"
#include <afxwin.h>

class TextEdit;
class ClassDiagramForm;
class TabKey : public KeyAction {
public:
	TabKey();
	TabKey(const TabKey& source);
	virtual ~TabKey();

	void KeyPress(TextEdit *textEdit);
	void KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc);
};

#endif // _TABKEY_H