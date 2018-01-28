//RemoveTemplateKey.h

#ifndef _REMOVETEMPLATEKEY_H
#define _REMOVETEMPLATEKEY_H

#include "KeyAction.h"
#include <afxwin.h>

class ClassDiagramForm;
class TextEdit;
class RemoveTemplateKey : public KeyAction {
public:
	RemoveTemplateKey();
	RemoveTemplateKey(const RemoveTemplateKey& source);
	virtual ~RemoveTemplateKey();

	void KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc);
	void KeyPress(TextEdit *textEdit);
};

#endif // _REMOVETEMPLATEKEY_H