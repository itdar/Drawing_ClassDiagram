//GraphicCtrlPasteMenuAction.h

#ifndef _GRAPHICCTRLPASTEMENUACTION_H
#define _GRAPHICCTRLPASTEMENUACTION_H

#include "MenuAction.h"

class LastClass;
class GraphicCtrlPasteMenuAction : public MenuAction {
public:
	GraphicCtrlPasteMenuAction();
	GraphicCtrlPasteMenuAction(const GraphicCtrlPasteMenuAction& source);
	~GraphicCtrlPasteMenuAction();
public:
	void MenuPress(LastClass *lastClass);
};

#endif // _GRAPHICCTRLPASTEMENUACTION_H
