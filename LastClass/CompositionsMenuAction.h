
#ifndef _COMPOSITIONSMENUACTION_H
#define _COMPOSITIONSMENUACTION_H
#include "MenuAction.h"

class CompositionsMenuAction : public MenuAction {
public:
	CompositionsMenuAction();
	virtual ~CompositionsMenuAction();
	void MenuPress(LastClass* lastClass);
};
#endif // !_COMPOSITIONSMENUACTION_H
