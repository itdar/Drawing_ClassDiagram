//GraphicCtrlCutMenuAction.h

#ifndef _GRAPHICCTRLCUTMENUACTION_H
#define _GRAPHICCTRLCUTMENUACTION_H

#include "MenuAction.h"

class LastClass;
class GraphicCtrlCutMenuAction : public MenuAction {
public:
	GraphicCtrlCutMenuAction();
	GraphicCtrlCutMenuAction(const GraphicCtrlCutMenuAction& source);
	~GraphicCtrlCutMenuAction();
public:
	void MenuPress(LastClass *lastClass);
};

#endif // _GRAPHICCTRLCUTMENUACTION_H
