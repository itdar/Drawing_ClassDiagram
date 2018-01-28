//PrintPreviewButtonAction.h

#ifndef _PRINTPREVIEWBUTTONACTION_H
#define _PRINTPREVIEWBUTTONACTION_H

class PrintPreview;
class PrintPreviewButtonAction {
public:
	PrintPreviewButtonAction();
	PrintPreviewButtonAction(const PrintPreviewButtonAction& source);
	virtual ~PrintPreviewButtonAction();
public:
	virtual void ButtonPress(PrintPreview *printPreview) = 0;
};

#endif // _PRINTPREVIEWBUTTONACTION_H