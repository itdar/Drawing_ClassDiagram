
#ifndef _ADDATTRIBUTEMENUACTION_H
#define _ADDATTRIBUTEMENUACTION_H
#include "MenuAction.h"

class AddAttributeMenuAction : public MenuAction {
public:
	AddAttributeMenuAction();
	virtual ~AddAttributeMenuAction();
	void MenuPress(LastClass* lastClass);
};
#endif // !_ADDATTRIBUTEMENUACTION_H
