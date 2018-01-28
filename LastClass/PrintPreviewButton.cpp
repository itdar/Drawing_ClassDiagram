//PrintPreviewButton.cpp

#include "PrintPreviewButton.h"
#include "PrintPreviewNextButton.h"
#include "PrintPreviewPreviousButton.h"
#include "PrintPreviewPrintButton.h"

PrintPreviewButton::PrintPreviewButton() {
}

PrintPreviewButton::PrintPreviewButton(const PrintPreviewButton& source) {
}

PrintPreviewButton::~PrintPreviewButton() {
	if (this->printPreviewButtonAction != 0) {
		delete this->printPreviewButtonAction;
	}
}

PrintPreviewButtonAction* PrintPreviewButton::ButtonPressed(UINT idNumber) {
	if (this->printPreviewButtonAction != 0) {
		delete this->printPreviewButtonAction;
	}
	switch (idNumber) {
	case 1:
		this->printPreviewButtonAction = new PrintPreviewNextButton;
		break;
	case 2:
		this->printPreviewButtonAction = new PrintPreviewPreviousButton;
		break;
	case 3:
		this->printPreviewButtonAction = new PrintPreviewPrintButton;
		break;
	/*case 4:
		this->printPreviewButtonAction = new PrintPreviewZoomInButton;
		break;
	case 5:
		this->printPreviewButtonAction = new PrintPreviewZoomOutButton;
		break;*/
	default: break;
	}
	return this->printPreviewButtonAction;
}