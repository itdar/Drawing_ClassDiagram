
#ifndef _DELETETEMPLATEMENUACTION_H
#define _DELETETEMPLATEMENUACTION_H
#include "MenuAction.h"

class DeleteTemplateMenuAction : public MenuAction {
public:
	DeleteTemplateMenuAction();
	virtual ~DeleteTemplateMenuAction();
	void MenuPress(LastClass* lastClass);
};
#endif // !_DELETETEMPLATEMENUACTION_H
