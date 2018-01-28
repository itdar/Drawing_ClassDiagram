//AddMethodKey.h

#ifndef _ADDMETHODKEY_H
#define _ADDMETHODKEY_H

#include "KeyAction.h"
#include <afxwin.h>

class ClassDiagramForm;
class TextEdit;
class AddMethodKey : public KeyAction {
public:
	AddMethodKey();
	AddMethodKey(const AddMethodKey& source);
	virtual ~AddMethodKey();

	void KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc);
	void KeyPress(TextEdit *textEdit);
};

#endif // _ADDMETHODKEY_H
