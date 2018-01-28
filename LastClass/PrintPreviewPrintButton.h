//PrintPreviewPrintButton.h

#ifndef _PRINTPREVIEWPRINTBUTTON_H
#define _PRINTPREVIEWPRINTBUTTON_H

#include "PrintPreviewButtonAction.h"

class PrintPreviewPrintButton : public PrintPreviewButtonAction {
public:
	PrintPreviewPrintButton();
	PrintPreviewPrintButton(const PrintPreviewPrintButton& source);
	virtual ~PrintPreviewPrintButton();
public:
	void ButtonPress(PrintPreview *printPreview);
};

#endif // _PRINTPREVIEWPRINTBUTTON_H