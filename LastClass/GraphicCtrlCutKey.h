///GraphicCtrlCutKey.h

#ifndef _GRAPHICCTRLCUTKEY_H
#define _GRAPHICCTRLCUTKEY_H

#include "KeyAction.h"
#include <afxwin.h>

class ClassDiagramForm;
class TextEdit;
class GraphicCtrlCutKey : public KeyAction {
public:
	GraphicCtrlCutKey();
	GraphicCtrlCutKey(const GraphicCtrlCutKey& source);
	virtual ~GraphicCtrlCutKey();

	virtual void KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc);
	virtual void KeyPress(TextEdit *textEdit);
};

#endif // _GRAPHICCTRLCUTKEY_H

