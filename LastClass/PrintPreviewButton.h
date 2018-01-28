//PrintPreviewButton.h

#include <afxdlgs.h>

#ifndef _PRINTPREVIEWBUTTON_H
#define _PRINTPREVIEWBUTTON_H

class PrintPreviewButtonAction;
class PrintPreviewButton {
public:
	PrintPreviewButton();
	PrintPreviewButton(const PrintPreviewButton& source);
	~PrintPreviewButton();
public:
	PrintPreviewButtonAction* ButtonPressed(UINT idNumber);
public:
	PrintPreviewButtonAction *printPreviewButtonAction;
};

#endif // _PRINTPREVIEWBUTTON_H