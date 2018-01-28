//GraphicLeftArrowKey.h

#ifndef _GRAPHICLEFTARROWKEY_H
#define _GRAPHICLEFTARROWKEY_H

#include "KeyAction.h"
#include <afxwin.h>

class TextEdit;
class ClassDiagramForm;
class GraphicLeftArrowKey : public KeyAction {
public:
	GraphicLeftArrowKey();
	GraphicLeftArrowKey(const GraphicLeftArrowKey& source);
	~GraphicLeftArrowKey();
public:
	void KeyPress(TextEdit *textEdit);
	void KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc);
};

#endif // _GRAPHICLEFTARROWKEY_H

