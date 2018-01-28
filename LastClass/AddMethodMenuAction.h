
#ifndef _ADDMETHODMENUACTION_H
#define _ADDMETHODMENUACTION_H
#include "MenuAction.h"

class AddMethodMenuAction : public MenuAction {
public:
	AddMethodMenuAction();
	virtual ~AddMethodMenuAction();
	void MenuPress(LastClass* lastClass);
};
#endif // !_ADDMETHODMENUACTION_H
