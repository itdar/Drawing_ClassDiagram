//GraphicCtrlCopyMenuAction.h

#ifndef _GRAPHICCTRLCOPYMENUACTION_H
#define _GRAPHICCTRLCOPYMENUACTION_H

#include "MenuAction.h"

class LastClass;
class GraphicCtrlCopyMenuAction : public MenuAction {
public:
	GraphicCtrlCopyMenuAction();
	GraphicCtrlCopyMenuAction(const GraphicCtrlCopyMenuAction& source);
	~GraphicCtrlCopyMenuAction();
public:
	void MenuPress(LastClass *lastClass);
};

#endif // _GRAPHICCTRLCOPYMENUACTION_H
