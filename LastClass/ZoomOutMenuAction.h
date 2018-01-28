//ZoomOutMenuAction.h

#ifndef _ZOOMOUTMENUACTION_H
#define _ZOOMOUTMENUACTION_H

#include "MenuAction.h"

class LastClass;
class ZoomOutMenuAction : public MenuAction {
public:
	ZoomOutMenuAction();
	ZoomOutMenuAction(const ZoomOutMenuAction& source);
	~ZoomOutMenuAction();
public:
	void MenuPress(LastClass *lastClass);
};

#endif // _ZOOMOUTMENUACTION_H

