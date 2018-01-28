//AboutMenuAction.h

#ifndef _ABOUTMENUACTION_H
#define _ABOUTMENUACTION_H
#include "MenuAction.h"

class AboutMenuAction : public MenuAction {
public:
	AboutMenuAction();
	virtual ~AboutMenuAction();
	void MenuPress(LastClass* lastClass);
};
#endif // !_ABOUTMENUACTION_H
