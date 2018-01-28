//PrintPreviewPreviousButton.cpp

#include "PrintPreviewPreviousButton.h"
#include "PrintPreview.h"

PrintPreviewPreviousButton::PrintPreviewPreviousButton() {
}

PrintPreviewPreviousButton::PrintPreviewPreviousButton(const PrintPreviewPreviousButton& source) {
}

PrintPreviewPreviousButton::~PrintPreviewPreviousButton() {
}

void PrintPreviewPreviousButton::ButtonPress(PrintPreview *printPreview) {
	printPreview->verticalPage -= printPreview->verticalPageSize;
	if (printPreview->verticalPage < 0) {
		printPreview->horizontalPage -= printPreview->horizontalPageSize;
		if (printPreview->horizontalPage < 0) {
			printPreview->horizontalPage = 0;
			printPreview->verticalPage = 0;
		}
		else {
			if (printPreview->verticalPaperSize % printPreview->verticalPageSize == 0) {
				printPreview->verticalPage = (printPreview->verticalPaperSize / printPreview->verticalPageSize - 1)*printPreview->verticalPageSize;
			}
			else {
				printPreview->verticalPage = (printPreview->verticalPaperSize / printPreview->verticalPageSize)*printPreview->verticalPageSize;
			}

		}
	}
	printPreview->Invalidate(false);
}