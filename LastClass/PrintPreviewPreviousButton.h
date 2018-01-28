//PrintPreviewPreviousButton.h

#ifndef _PRINTPREVIEWPREVIOUSBUTTON_H
#define _PRINTPREVIEWPREVIOUSBUTTON_H

#include "PrintPreviewButtonAction.h"

class PrintPreviewPreviousButton : public PrintPreviewButtonAction {
public:
	PrintPreviewPreviousButton();
	PrintPreviewPreviousButton(const PrintPreviewPreviousButton& source);
	virtual ~PrintPreviewPreviousButton();
public:
	void ButtonPress(PrintPreview *printPreview);
};

#endif // _PRINTPREVIEWPREVIOUSBUTTON_H