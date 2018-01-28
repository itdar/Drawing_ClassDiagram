#ifndef _GENERALIZATIONMENUACTION_H
#define _GENERALIZATIONMENUACTION_H

#include "MenuAction.h"

class GeneralizationMenuAction : public MenuAction {
public:
	GeneralizationMenuAction();
	virtual ~GeneralizationMenuAction();
	void MenuPress(LastClass* lastClass);
};
#endif // !_GENERALIZATIONMENUACTION_H
