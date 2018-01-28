
#ifndef _ADDTEMPLATEMENUACTION_H
#define _ADDTEMPLATEMENUACTION_H
#include "MenuAction.h"

class AddTemplateMenuAction : public MenuAction {
public:
	AddTemplateMenuAction();
	virtual ~AddTemplateMenuAction();
	void MenuPress(LastClass* lastClass);
};
#endif // !_ADDTEMPLATEMENUACTION_H
