//GraphicCtrlPasteKey.h

#ifndef _GRAPHICCTRLPASTEKEY_H
#define _GRAPHICCTRLPASTEKEY_H

#include "KeyAction.h"
#include <afxwin.h>

class ClassDiagramForm;
class TextEdit;
class GraphicCtrlPasteKey : public KeyAction {
public:
	GraphicCtrlPasteKey();
	GraphicCtrlPasteKey(const GraphicCtrlPasteKey& source);
	virtual ~GraphicCtrlPasteKey();

	virtual void KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc);
	virtual void KeyPress(TextEdit *textEdit);
};

#endif // _GRAPHICCTRLPASTEKEY_H


