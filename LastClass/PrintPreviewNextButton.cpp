//PrintPreviewNextButton.cpp

#include "PrintPreviewNextButton.h"
#include "PrintPreview.h"

PrintPreviewNextButton::PrintPreviewNextButton() {
}

PrintPreviewNextButton::PrintPreviewNextButton(const PrintPreviewNextButton& source) {
}

PrintPreviewNextButton::~PrintPreviewNextButton() {
}

void PrintPreviewNextButton::ButtonPress(PrintPreview *printPreview) {
	printPreview->verticalPage += printPreview->verticalPageSize;
	if (printPreview->verticalPage >= printPreview->verticalPaperSize) {
		printPreview->horizontalPage += printPreview->horizontalPageSize;;
		if (printPreview->horizontalPage >= printPreview->horizontalPaperSize) {
			printPreview->horizontalPage -= printPreview->horizontalPageSize;
			printPreview->verticalPage -= printPreview->verticalPageSize;
		}
		else {
			printPreview->verticalPage = 0;
		}
	}
	printPreview->Invalidate(false);
}