#ifndef _SUPPORTMENUACTION_H
#define _SUPPORTMENUACTION_H
#include "MenuAction.h"

class SupportMenuAction : public MenuAction {
public:
	SupportMenuAction();
	virtual ~SupportMenuAction();
	void MenuPress(LastClass* lastClass);
};
#endif // !_SUPPORTMENUACTION_H
