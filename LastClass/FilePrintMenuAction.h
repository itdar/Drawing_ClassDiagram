#ifndef _FILEPRINTMENUACTION_H
#define _FILEPRINTMENUACTION_H

#include "MenuAction.h"

class FilePrintMenuAction : public MenuAction {
public:
	FilePrintMenuAction();
	virtual ~FilePrintMenuAction();
	void MenuPress(LastClass* lastClass);
};
#endif // !_FILEPRINTMENUACTION_H
