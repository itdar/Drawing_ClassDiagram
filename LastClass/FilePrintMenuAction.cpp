#include "FilePrintMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "Selection.h"
#include "Diagram.h"
#include "DrawingVisitor.h"
#include "PrintPreview.h"
#include "Finder.h"
#include "FigureComposite.h"
#include "KnockKnock.h"
#include "ResizeVisitor.h"
#include "Relation.h"
#include "ScrollMovingObject.h"

FilePrintMenuAction::FilePrintMenuAction() {
}
FilePrintMenuAction::~FilePrintMenuAction() {
}
void FilePrintMenuAction::MenuPress(LastClass* lastClass) {


	CPrintDialog printDialog(FALSE, PD_ALLPAGES | PD_RETURNDC, lastClass);

	INT_PTR int_ptr = AfxGetApp()->DoPrintDialog(&printDialog);


	if (int_ptr == IDOK) {
		ScrollMovingObject scrollMovingObject;
		SCROLLINFO vScinfo;
		SCROLLINFO hScinfo;

		ScrollMovingObject moving;
		lastClass->classDiagramForm->GetScrollInfo(SB_VERT, &vScinfo);
		lastClass->classDiagramForm->GetScrollInfo(SB_HORZ, &hScinfo);


		Long zoomRate = lastClass->classDiagramForm->zoomRate;
		ResizeVisitor visitor1(lastClass->classDiagramForm->zoomRate, 100);
		lastClass->classDiagramForm->zoomRate = 100;
		lastClass->classDiagramForm->SetMemoGab(20 * lastClass->classDiagramForm->zoomRate / 100);
		lastClass->classDiagramForm->SetGabX(8 * lastClass->classDiagramForm->zoomRate / 100);
		lastClass->classDiagramForm->SetGabY(2 * lastClass->classDiagramForm->zoomRate / 100);
		lastClass->classDiagramForm->SetCaretWidth(2 * lastClass->classDiagramForm->zoomRate / 100);
		CDC memDC;
		lastClass->classDiagramForm->diagram->Accept(visitor1, &memDC);

		KnockKnock *knocking = new KnockKnock;
		knocking->Knocking(lastClass->classDiagramForm);

		scrollMovingObject.MovingObject(lastClass->classDiagramForm->diagram, hScinfo.nPos, vScinfo.nPos);
		bool ret = false;
		Long xLimit = scrollMovingObject.GetHorizontalMax(lastClass->classDiagramForm->diagram);
		Long yLimit = scrollMovingObject.GetVerticalMax(lastClass->classDiagramForm->diagram);
		Long xPage = xLimit / 2000;
		Long yPage = yLimit / 2000;
		if (xLimit % 2000 != 0) {
			xPage++;
		}
		if (yLimit % 2000 != 0) {
			yPage++;
		}
		Long xPaper = xPage * 2000;
		Long yPaper = yPage * 2000;
		Long totalPage = xPage*yPage;

		CDC dc;
		int count = printDialog.GetCopies();
		dc.Attach(printDialog.GetPrinterDC());

		dc.m_bPrinting = TRUE;

		CString strTitle;
		strTitle.LoadString(AFX_IDS_APP_TITLE);
		DOCINFO di;
		ZeroMemory(&di, sizeof(DOCINFO));
		di.cbSize = sizeof(DOCINFO);
		di.lpszDocName = strTitle;
		Long currentX = 0;
		Long currentY = 0;
		Long i = 1;
		BOOL bPrintingOK = dc.StartDoc(&di);

		CPrintInfo Info;

		Info.m_rectDraw.SetRect(0, 0, dc.GetDeviceCaps(HORZRES), dc.GetDeviceCaps(VERTRES));
		Info.SetMaxPage(totalPage);

		//printPreview.OnBeginPrinting(&dc, &Info);

		while (i <= count) {

			for (UINT page = Info.GetMinPage(); page <= Info.GetMaxPage() && bPrintingOK; page++) {

				scrollMovingObject.MovingObject(lastClass->classDiagramForm->diagram, -currentX, -currentY);
				dc.StartPage();
				Info.m_nCurPage = page;
				//printPreview.OnPrint(&dc, &Info, page);

				//Long k = page - 1;

				Long width = Info.m_rectDraw.Width();
				Long hegiht = Info.m_rectDraw.Height();
				CDC memDC;
				CRect rect;
				lastClass->classDiagramForm->GetClientRect(&rect);
				CBitmap *pOldBitmap;
				CBitmap bitmap;

				CPaintDC pdc(lastClass);

				memDC.CreateCompatibleDC(&pdc);
				bitmap.CreateCompatibleBitmap(&pdc, 2000, 2000);
				pOldBitmap = memDC.SelectObject(&bitmap);
				memDC.FillSolidRect(CRect(0, 0, 2000, 2000), RGB(255, 255, 255));
				CFont cFont;//CreateFont에 값18을 textEdit의 rowHight로 바꿔야함
				Long ih = MulDiv(14 * lastClass->classDiagramForm->zoomRate / 100, GetDeviceCaps(pdc, LOGPIXELSY), 72);
				cFont.CreateFont(ih, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET,// 글꼴 설정
					OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "굴림체");
				lastClass->SetFont(&cFont, TRUE);
				CFont *oldFont = memDC.SelectObject(&cFont);

				DrawingVisitor drawingVisitor(100);
				lastClass->classDiagramForm->diagram->Accept(drawingVisitor, &memDC);
				//WritingVisitor writingVisitor(100);
				//lastClass->classDiagramForm->diagram->Accept(writingVisitor, &memDC);


				CBitmap *pOldBitmapOne;
				CBitmap bitmapOne;
				CDC memDCOne;
				memDCOne.CreateCompatibleDC(&pdc);
				bitmapOne.CreateCompatibleBitmap(&pdc, 2000, 2000);
				pOldBitmapOne = memDCOne.SelectObject(&bitmapOne);
				memDCOne.FillSolidRect(CRect(0, 0, 2000, 2000), RGB(255, 255, 255));
				memDCOne.BitBlt(0, 0, 2000, 2000, &memDC, 0, 0, SRCCOPY);

				int mapMode = dc.GetMapMode();
				memDCOne.SetMapMode(mapMode);
				dc.SetStretchBltMode(COLORONCOLOR);

				//cdc->SetMapMode(MM_ISOTROPIC);
				//cdc->SetWindowExt(100, 100);
				//cdc->SetViewportExt(this->zoomRate, this->zoomRate);

				dc.StretchBlt(100, 100, width - 200, hegiht - 200, &memDCOne, 0, 0, 2000, 2000, SRCCOPY);


				bPrintingOK = (dc.EndPage() > 0);

				memDC.SelectObject(oldFont);
				cFont.DeleteObject();
				memDC.SelectObject(pOldBitmap);
				bitmap.DeleteObject();
				memDC.DeleteDC();
				memDCOne.SelectObject(pOldBitmap);
				bitmapOne.DeleteObject();
				memDCOne.DeleteDC();
				scrollMovingObject.MovingObject(lastClass->classDiagramForm->diagram, currentX, currentY);
				currentY += 2000;
				if (currentY >= yPage * 2000) {
					currentX += 2000;
					currentY = 0;
				}
			}
			i++;

		}
		//printPreview.OnEndPrinting(&dc, &Info);
		if (bPrintingOK) dc.EndDoc();
		else dc.AbortDoc();

		dc.Detach();
		lastClass->classDiagramForm->zoomRate = zoomRate;
		ResizeVisitor visitor2(100, lastClass->classDiagramForm->zoomRate);
		lastClass->classDiagramForm->SetMemoGab(20 * lastClass->classDiagramForm->zoomRate / 100);
		lastClass->classDiagramForm->SetGabX(8 * lastClass->classDiagramForm->zoomRate / 100);
		lastClass->classDiagramForm->SetGabY(2 * lastClass->classDiagramForm->zoomRate / 100);
		lastClass->classDiagramForm->SetCaretWidth(2 * lastClass->classDiagramForm->zoomRate / 100);
		lastClass->classDiagramForm->diagram->Accept(visitor2, &memDC);
		knocking->Knocking(lastClass->classDiagramForm);
		if (knocking != NULL) {
			delete knocking;
		}

		scrollMovingObject.MovingObject(lastClass->classDiagramForm->diagram, -hScinfo.nPos, -vScinfo.nPos);

	}

}