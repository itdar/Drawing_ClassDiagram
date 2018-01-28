//MenuAction.h

#ifndef _MENUACTIOIN_H
#define _MENUACTIOIN_H

class LastClass;
class MenuAction {
public:
	MenuAction();
	virtual ~MenuAction();
	virtual void MenuPress(LastClass* lastClass) = 0;
};

#endif // !_MENUACTIOIN_H
