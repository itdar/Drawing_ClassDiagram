//ZoomInMenuAction.h

#ifndef _ZOOMINMENUACTION_H
#define _ZOOMINMENUACTION_H

#include "MenuAction.h"

class LastClass;
class ZoomInMenuAction : public MenuAction {
public:
	ZoomInMenuAction();
	ZoomInMenuAction(const ZoomInMenuAction& source);
	~ZoomInMenuAction();
public:
	void MenuPress(LastClass *lastClass);
};

#endif // _ZOOMINMENUACTION_H

