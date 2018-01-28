#ifndef _REALIZATIONMENUACTION_H
#define _REALIZATIONMENUACTION_H
#include "MenuAction.h"

class RealizationMenuAction : public MenuAction {
public:
	RealizationMenuAction();
	virtual ~RealizationMenuAction();
	void MenuPress(LastClass* lastClass);
};
#endif // !_REALIZATIONMENUACTION_H
