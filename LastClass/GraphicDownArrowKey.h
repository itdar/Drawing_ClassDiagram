//GraphicDownArrowKey.h

#ifndef _GRAPHICDOWNARROWKEY_H
#define _GRAPHICDOWNARROWKEY_H

#include "KeyAction.h"
#include <afxwin.h>

class TextEdit;
class ClassDiagramForm;
class GraphicDownArrowKey : public KeyAction {
public:
	GraphicDownArrowKey();
	GraphicDownArrowKey(const GraphicDownArrowKey& source);
	~GraphicDownArrowKey();
public:
	void KeyPress(TextEdit *textEdit);
	void KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc);
};

#endif // _GRAPHICDOWNARROWKEY_H
