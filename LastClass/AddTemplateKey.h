//AddTemplateKey.h

#ifndef _ADDTEMPLATEKEY_H
#define _ADDTEMPLATEKEY_H

#include "KeyAction.h"
#include <afxwin.h>

class ClassDiagramForm;
class TextEdit;
class AddTemplateKey : public KeyAction {
public:
	AddTemplateKey();
	AddTemplateKey(const AddTemplateKey& source);
	virtual ~AddTemplateKey();

	virtual void KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc);
	virtual void KeyPress(TextEdit *textEdit);
};

#endif // _ADDTEMPLATEKEY_H