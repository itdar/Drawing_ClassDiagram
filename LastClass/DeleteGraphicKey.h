//DeleteGraphicKey.h

#ifndef _DELETEGRAPHICKEY_H
#define _DELETEGRAPHICKEY_H

#include "KeyAction.h"
#include <afxwin.h>

class ClassDiagramForm;
class TextEdit;
class DeleteGraphicKey : public KeyAction {
public:
	DeleteGraphicKey();
	DeleteGraphicKey(const DeleteGraphicKey& source);
	virtual ~DeleteGraphicKey();

	void KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc);
	void KeyPress(TextEdit *textEdit);
};

#endif // _DELETEGRAPHICKEY_H