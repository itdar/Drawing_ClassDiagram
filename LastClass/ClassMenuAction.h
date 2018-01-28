#ifndef _CLASSMENUACTION_H
#define _CLASSMENUACTION_H

#include "MenuAction.h"

class ClassMenuAction : public MenuAction {
public:
	ClassMenuAction();
	virtual ~ClassMenuAction();
	void MenuPress(LastClass* lastClass);
};
#endif // !_CLASSMENUACTION_H
