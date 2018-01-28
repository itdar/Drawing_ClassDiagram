#ifndef _FILEPRINTPREVIEWMENUACTION_H
#define _FILEPRINTPREVIEWMENUACTION_H

#include "MenuAction.h"

class FilePrintPreviewMenuAction : public MenuAction {
public:
	FilePrintPreviewMenuAction();
	virtual ~FilePrintPreviewMenuAction();
	void MenuPress(LastClass* lastClass);
};
#endif // !_FILEPRINTPREVIEWMENUACTION_H
