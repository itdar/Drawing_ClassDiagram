//GraphicCtrlRedoKey.h

#include "KeyAction.h"

#ifndef _GRAPHICCTRLREDOKEY_H
#define _GRAPHICCTRLREDOKEY_H

class ClassDiagramForm;
class TextEdit;
class GraphicCtrlRedoKey : public KeyAction {
public:
	GraphicCtrlRedoKey();
	GraphicCtrlRedoKey(const GraphicCtrlRedoKey& source);
	virtual ~GraphicCtrlRedoKey();

	virtual void KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc);
	virtual void KeyPress(TextEdit *textEdit);
};

#endif _GRAPHICCTRLREDOKEY_H