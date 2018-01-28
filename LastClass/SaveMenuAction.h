#ifndef _SAVEMENUACTION_H
#define _SAVEMENUACTION_H

#include "MenuAction.h"

class SaveMenuAction : public MenuAction {
public:
	SaveMenuAction();
	virtual ~SaveMenuAction();
	void MenuPress(LastClass* lastClass);
};
#endif // !_SAVEMENUACTION_H
