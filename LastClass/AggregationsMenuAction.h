
#ifndef _AGGREGATIONSMENUACTION_H
#define _AGGREGATIONSMENUACTION_H
#include "MenuAction.h"

class AggregationsMenuAction : public MenuAction {
public:
	AggregationsMenuAction();
	virtual ~AggregationsMenuAction();
	void MenuPress(LastClass* lastClass);
};
#endif // !_AGGREGATIONSMENUACTION_H
