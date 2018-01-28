
#ifndef _COMPOSITIONMENUACTION_H
#define _COMPOSITIONMENUACTION_H
#include "MenuAction.h"

class CompositionMenuAction : public MenuAction {
public:
	CompositionMenuAction();
	virtual ~CompositionMenuAction();
	void MenuPress(LastClass* lastClass);
};
#endif // !_COMPOSITIONMENUACTION_H
