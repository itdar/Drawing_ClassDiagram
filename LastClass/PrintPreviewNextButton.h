//PrintPreviewNextButton.h

#ifndef _PRINTPREVIEWNEXTBUTTON_H
#define _PRINTPREVIEWNEXTBUTTON_H

#include "PrintPreviewButtonAction.h"

class PrintPreviewNextButton : public PrintPreviewButtonAction {
public:
	PrintPreviewNextButton();
	PrintPreviewNextButton(const PrintPreviewNextButton& source);
	virtual ~PrintPreviewNextButton();
public:
	void ButtonPress(PrintPreview *printPreview);
};

#endif // _PRINTPREVIEWNEXTBUTTON_H