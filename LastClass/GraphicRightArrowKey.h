//GraphicRightArrowKey.h

#ifndef _GRAPHICRIGHTARROWKEY_H
#define _GRAPHICRIGHTARROWKEY_H

#include "KeyAction.h"
#include <afxwin.h>

class TextEdit;
class ClassDiagramForm;
class GraphicRightArrowKey : public KeyAction {
public:
	GraphicRightArrowKey();
	GraphicRightArrowKey(const GraphicRightArrowKey& source);
	~GraphicRightArrowKey();
public:
	void KeyPress(TextEdit *textEdit);
	void KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc);
};

#endif // _GRAPHICRIGHTARROWKEY_H


