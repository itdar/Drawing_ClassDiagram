
#ifndef _ADDRECEPTIONMENUACTION_H
#define _ADDRECEPTIONMENUACTION_H
#include "MenuAction.h"

class AddReceptionMenuAction : public MenuAction {
public:
	AddReceptionMenuAction();
	virtual ~AddReceptionMenuAction();
	void MenuPress(LastClass* lastClass);
};
#endif // !_ADDRECEPTIONMENUACTION_H
