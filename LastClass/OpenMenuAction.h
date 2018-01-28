#ifndef _OPENMENUACTION_H
#define _OPENMENUACTION_H

#include "MenuAction.h"

class OpenMenuAction : public MenuAction {
public:
	OpenMenuAction();
	virtual ~OpenMenuAction();
	void MenuPress(LastClass* lastClass);
};
#endif // !_OPENMENUACTION_H
