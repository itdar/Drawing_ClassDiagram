//GraphicUpArrowKey.h

#ifndef _GRAPHICUPARROWKEY_H
#define _GRAPHICUPARROWKEY_H

#include "KeyAction.h"
#include <afxwin.h>

class TextEdit;
class ClassDiagramForm;
class GraphicUpArrowKey : public KeyAction {
public:
	GraphicUpArrowKey();
	GraphicUpArrowKey(const GraphicUpArrowKey& source);
	~GraphicUpArrowKey();
public:
	void KeyPress(TextEdit *textEdit);
	void KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc);
};

#endif // _GRAPHICUPARROWKEY_H

