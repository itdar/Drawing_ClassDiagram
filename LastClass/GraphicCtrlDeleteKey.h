//GraphicCtrlDeleteKey.h

#ifndef _GRAPHICCTRLDELETEKEY_H
#define _GRAPHICCTRLDELETEKEY_H

#include "KeyAction.h"
#include <afxwin.h>

class TextEdit;
class ClassDiagramForm;
class GraphicCtrlDeleteKey : public KeyAction {
public:
	GraphicCtrlDeleteKey();
	GraphicCtrlDeleteKey(const GraphicCtrlDeleteKey& source);
	~GraphicCtrlDeleteKey();
public:
	void KeyPress(TextEdit *textEdit);
	void KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc);
};

#endif // _GRAPHICCTRLDELETEKEY_H