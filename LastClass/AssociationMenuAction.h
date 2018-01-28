
#ifndef _ASSOCIATIONMENUACTION_H	
#define _ASSOCIATIONMENUACTION_H
#include "MenuAction.h"

class AssociationMenuAction : public MenuAction {
public:
	AssociationMenuAction();
	virtual ~AssociationMenuAction();
	void MenuPress(LastClass* lastClass);
};
#endif // !_ASSOCIATIONMENUACTION_H
