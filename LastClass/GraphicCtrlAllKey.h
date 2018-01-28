//GraphicCtrlAllKey.h

#ifndef _GRAPHICCTRLALLKEY_H
#define _GRAPHICCTRLALLKEY_H

#include "KeyAction.h"

class ClassDiagramForm;
class GraphicCtrlAllKey : public KeyAction {
public:
	GraphicCtrlAllKey();
	GraphicCtrlAllKey(const GraphicCtrlAllKey& source);
	virtual ~GraphicCtrlAllKey();
public:
	void KeyPress(ClassDiagramForm *classDiagramForm,CDC *cdc);
	void KeyPress(TextEdit *textEdit);
};

#endif // _GRAPHICCTRLALLKEY_H