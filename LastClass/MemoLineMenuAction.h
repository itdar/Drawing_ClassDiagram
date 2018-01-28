
#ifndef _MEMOLINEMENUACTION_H
#define _MEMOLINEMENUACTION_H
#include "MenuAction.h"

class MemoLineMenuAction : public MenuAction {
public:
	MemoLineMenuAction();
	virtual ~MemoLineMenuAction();
	void MenuPress(LastClass* lastClass);
};
#endif // !_MEMOLINEMENUACTION_H
