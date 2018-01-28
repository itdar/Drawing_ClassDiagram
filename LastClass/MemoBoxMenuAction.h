#ifndef _MEMOBOXMENUACTION_H
#define _MEMOBOXMENUACTION_H

#include "MenuAction.h"

class MemoBoxMenuAction : public MenuAction {
public:
	MemoBoxMenuAction();
	virtual ~MemoBoxMenuAction();
	void MenuPress(LastClass* lastClass);
};
#endif // !_MEMOBOXMENUACTION_H
