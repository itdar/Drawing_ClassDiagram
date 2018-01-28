//AddReceptionKey.h

#ifndef _ADDRECEPTIONKEY_H
#define _ADDRECEPTIONKEY_H

#include "KeyAction.h"
#include <afxwin.h>

class ClassDiagramForm;
class TextEdit;
class AddReceptionKey : public KeyAction {
public:
	AddReceptionKey();
	AddReceptionKey(const AddReceptionKey& source);
	virtual ~AddReceptionKey();

	void KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc);
	void KeyPress(TextEdit *textEdit);
};

#endif // _ADDRECEPTIONKEY_H
