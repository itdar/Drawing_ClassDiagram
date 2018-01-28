#ifndef _SAVEASMENUACTION_H
#define _SAVEASMENUACTION_H

#include "MenuAction.h"

class SaveAsMenuAction : public MenuAction {
public:
	SaveAsMenuAction();
	virtual ~SaveAsMenuAction();
	void MenuPress(LastClass* lastClass);
};
#endif // !_SAVEASMENUACTION_H
