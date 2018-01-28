//ExitKeyMenuAction.h

#ifndef _EXITKEYMENUACTION_H
#define _EXITKEYMENUACTION_H

#include "MenuAction.h"

class LastClass;
class ExitKeyMenuAction : public MenuAction {
public:
	ExitKeyMenuAction();
	ExitKeyMenuAction(const ExitKeyMenuAction& source);
	virtual ~ExitKeyMenuAction();
public:
	void MenuPress(LastClass *lastClass);
};

#endif // _EXITKEYMENUACTION_H