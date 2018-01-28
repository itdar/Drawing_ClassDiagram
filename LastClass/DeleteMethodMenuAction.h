
#ifndef _DELETEMETHODMENUACTION_H
#define _DELETEMETHODMENUACTION_H
#include "MenuAction.h"

class DeleteMethodMenuAction : public MenuAction {
public:
	DeleteMethodMenuAction();
	virtual ~DeleteMethodMenuAction();
	void MenuPress(LastClass* lastClass);
};
#endif // !_DELETEMETHODMENUACTION_H
