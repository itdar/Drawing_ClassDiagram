//PrintPreviewPrintButton.cpp

#include "PrintPreviewPrintButton.h"
#include "PrintPreview.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "Diagram.h"
#include "Finder.h"
#include "FigureComposite.h"
#include "ScrollMovingObject.h"
#include "Relation.h"

PrintPreviewPrintButton::PrintPreviewPrintButton() {
}

PrintPreviewPrintButton::PrintPreviewPrintButton(const PrintPreviewPrintButton& source) {
}

PrintPreviewPrintButton::~PrintPreviewPrintButton() {
}

void PrintPreviewPrintButton::ButtonPress(PrintPreview *printPreview) {

	CPrintDialog printDialog(FALSE, PD_ALLPAGES | PD_RETURNDC, printPreview);


	INT_PTR int_ptr = AfxGetApp()->DoPrintDialog(&printDialog);


	if (int_ptr == IDOK) {
		bool ret = false;
		ScrollMovingObject scrollMovingObject;
		Long horizontalLimit = scrollMovingObject.GetHorizontalMax(printPreview->lastClass->classDiagramForm->diagram);
		Long horizontalPage = horizontalLimit / (printPreview->horizontalPageSize);
		if (horizontalLimit % (printPreview->horizontalPageSize) != 0) {
			horizontalPage++;
		}
		Long verticalLimit = scrollMovingObject.GetVerticalMax(printPreview->lastClass->classDiagramForm->diagram);
		Long verticalPage = verticalLimit / (printPreview->verticalPageSize);
		if (verticalLimit % (printPreview->verticalPageSize) != 0) {
			verticalPage++;
		}
		Long totalPage = horizontalPage*verticalPage;

		CDC dc;
		int count = printDialog.GetCopies();
		Long i = 1;
		dc.Attach(printDialog.GetPrinterDC());

		dc.m_bPrinting = TRUE;

		CString strTitle;
		strTitle.LoadString(AFX_IDS_APP_TITLE);
		DOCINFO di;
		ZeroMemory(&di, sizeof(DOCINFO));
		di.cbSize = sizeof(DOCINFO);
		di.lpszDocName = strTitle;

		BOOL bPrintingOK = dc.StartDoc(&di);

		CPrintInfo Info;

		Info.m_rectDraw.SetRect(0, 0, dc.GetDeviceCaps(HORZRES), dc.GetDeviceCaps(VERTRES));
		Info.SetMaxPage(totalPage);
		printPreview->OnBeginPrinting(&dc, &Info);
		i = 1;
		while (i <= count) {
			for (UINT page = Info.GetMinPage(); page <= Info.GetMaxPage() && bPrintingOK; page++) {

				dc.StartPage();
				Info.m_nCurPage = page;
				printPreview->OnPrint(&dc, &Info, page);
				bPrintingOK = (dc.EndPage() > 0);

			}
			i++;

		}
		printPreview->OnEndPrinting(&dc, &Info);
		if (bPrintingOK) dc.EndDoc();
		else dc.AbortDoc();

		dc.Detach();
	}

}