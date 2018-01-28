
#ifndef _DELETEMENUACTION_H
#define _DELETEMENUACTION_H
#include "MenuAction.h"

class DeleteMenuAction : public MenuAction {
public:
	DeleteMenuAction();
	virtual ~DeleteMenuAction();
	void MenuPress(LastClass* lastClass);
};
#endif // !_DELETEMENUACTION_H
