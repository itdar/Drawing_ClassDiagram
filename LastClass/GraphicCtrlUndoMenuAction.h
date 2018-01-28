//GraphicCtrlUndoMenuAction.h

#ifndef _GRAPHICCTRLUNDOMENUACTION_H
#define _GRAPHICCTRLUNDOMENUACTION_H

#include "MenuAction.h"

class LastClass;
class GraphicCtrlUndoMenuAction : public MenuAction {
public:
	GraphicCtrlUndoMenuAction();
	GraphicCtrlUndoMenuAction(const GraphicCtrlUndoMenuAction& source);
	~GraphicCtrlUndoMenuAction();
public:
	void MenuPress(LastClass *lastClass);
};

#endif // _GRAPHICCTRLUNDOMENUACTION_H