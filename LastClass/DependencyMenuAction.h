#ifndef _DEPENDENCYMENUACTION_H	
#define _DEPENDENCYMENUACTION_H
#include "MenuAction.h"

class DependencyMenuAction : public MenuAction {
public:
	DependencyMenuAction();
	virtual ~DependencyMenuAction();
	void MenuPress(LastClass* lastClass);
};
#endif // !_DEPENDENCYMENUACTION_H
