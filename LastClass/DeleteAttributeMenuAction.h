
#ifndef _DELETEATTRIBUTEMENUACTION_H
#define _DELETEATTRIBUTEMENUACTION_H
#include "MenuAction.h"

class DeleteAttributeMenuAction : public MenuAction {
public:
	DeleteAttributeMenuAction();
	virtual ~DeleteAttributeMenuAction();
	void MenuPress(LastClass* lastClass);
};
#endif // !_DELETEATTRIBUTEMENUACTION_H
