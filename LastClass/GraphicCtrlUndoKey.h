//GraphicCtrlUndoKey.h

#include "KeyAction.h"
#include <afxwin.h>

#ifndef _GRAPHICCTRLUNDOKEY_H
#define _GRAPHICCTRLUNDOKEY_H

class ClassDiagramForm;
class TextEdit;
class GraphicCtrlUndoKey : public KeyAction {
public:
	GraphicCtrlUndoKey();
	GraphicCtrlUndoKey(const GraphicCtrlUndoKey& source);
	virtual ~GraphicCtrlUndoKey();

	virtual void KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc);
	virtual void KeyPress(TextEdit *textEdit);
};

#endif _GRAPHICCTRLUNDOKEY_H