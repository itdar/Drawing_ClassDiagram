
#ifndef _DELETERECEPTIONMENUACTION_H
#define _DELETERECEPTIONMENUACTION_H
#include "MenuAction.h"

class DeleteReceptionMenuAction : public MenuAction {
public:
	DeleteReceptionMenuAction();
	virtual ~DeleteReceptionMenuAction();
	void MenuPress(LastClass* lastClass);
};
#endif // !_DELETERECEPTIONMENUACTION_H
