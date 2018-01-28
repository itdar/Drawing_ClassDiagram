//GraphicCtrlCopyKey.h

#ifndef _GRAPHICCTRLCOPYKEY_H
#define _GRAPHICCTRLCOPYKEY_H

#include "KeyAction.h"
#include <afxwin.h>

class ClassDiagramForm;
class TextEdit;
class GraphicCtrlCopyKey : public KeyAction {
public:
	GraphicCtrlCopyKey();
	GraphicCtrlCopyKey(const GraphicCtrlCopyKey& source);
	virtual ~GraphicCtrlCopyKey();

	virtual void KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc);
	virtual void KeyPress(TextEdit *textEdit);
};

#endif // _GRAPHICCTRLCOPYKEY_H

