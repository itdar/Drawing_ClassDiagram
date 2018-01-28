//DeleteGraphicKeyMenuAction.h

#ifndef _DELETEGRAPHICKEYMENUACTION_H
#define _DELETEGRAPHICKEYMENUACTION_H

#include "MenuAction.h"

class LastClass;
class DeleteGraphicKeyMenuAction : public MenuAction {
public:
	DeleteGraphicKeyMenuAction();
	DeleteGraphicKeyMenuAction(const DeleteGraphicKeyMenuAction& source);
	~DeleteGraphicKeyMenuAction();
public:
	void MenuPress(LastClass *lastClass);
};

#endif // _DELETEGRAPHICKEYMENUACTION_H

