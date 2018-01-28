//GraphicCtrlRedoMenuAction.h

#ifndef _GRAPHICCTRLREDOMENUACTION_H
#define _GRAPHICCTRLREDOMENUACTION_H

#include "MenuAction.h"

class LastClass;
class GraphicCtrlRedoMenuAction : public MenuAction {
public:
	GraphicCtrlRedoMenuAction();
	GraphicCtrlRedoMenuAction(const GraphicCtrlRedoMenuAction& source);
	~GraphicCtrlRedoMenuAction();
public:
	void MenuPress(LastClass *lastClass);
};

#endif // _GRAPHICCTRLREDOMENUACTION_H