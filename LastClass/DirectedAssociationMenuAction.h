
#ifndef _DIRECTEDASSOCIATIONMENUACTION_H	
#define _DIRECTEDASSOCIATIONMENUACTION_H
#include "MenuAction.h"

class DirectedAssociationMenuAction : public MenuAction {
public:
	DirectedAssociationMenuAction();
	virtual ~DirectedAssociationMenuAction();
	void MenuPress(LastClass* lastClass);
};
#endif // !_DIRECTEDASSOCIATIONMENUACTION_H
