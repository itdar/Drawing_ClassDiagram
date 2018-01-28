//TextAreaSelected.cpp

#include "TextAreaSelected.h"
#include "TextAreaSelectedProcess.h"
#include "ClassDiagramForm.h"
#include "TextEdit.h"
#include "Caret.h"
#include "Text.h"
#include "Row.h"
#include "Character.h"
#include "Figure.h"
#include "FontSet.h"
#include "DrawingVisitor.h"

TextAreaSelected::TextAreaSelected() {
	this->selected = new TextAreaSelectedProcess;
}
TextAreaSelected::TextAreaSelected(const TextAreaSelected& source) {
}
TextAreaSelected::~TextAreaSelected() {
	if (this->selected != 0) {
		delete selected;
	}
}
void TextAreaSelected::SelectTextArea(TextEdit *textEdit, CDC *pDC) {
	
	CString TopCstr;
	CString middleCstr;
	CString BottomCstr;
	RECT rt;

	pDC->SetTextColor(RGB(255, 255, 255));
	pDC->SetBkColor(RGB(51, 153, 255));
	pDC->SetBkMode(OPAQUE);//텍스트 배경을 SetBkColor 사용

	selected->GetRange(textEdit);
	if (textEdit->selectedY == textEdit->caret->GetRowIndex()) {
		this->selected->SingleLineSelected(textEdit, pDC, &TopCstr, &rt);
		pDC->DrawText(TopCstr, &rt, DT_EXPANDTABS);
	}
	else {
		this->selected->FirstMultiLineSelected(textEdit, pDC, &TopCstr, &rt);
		pDC->DrawText(TopCstr, &rt, DT_EXPANDTABS);
		if (this->selected->GetStartRowIndex() + 1 < this->selected->GetEndRowIndex()) {
			this->selected->MiddleMultiLineSelected(textEdit, pDC, &middleCstr, &rt);
			pDC->DrawText(middleCstr, &rt, DT_EXPANDTABS);
		}

		this->selected->EndMultiLineSelected(textEdit, pDC, &BottomCstr, &rt);
		pDC->DrawText(BottomCstr, &rt, DT_EXPANDTABS);
	}

	
	textEdit->copyBuffer = TopCstr + middleCstr + BottomCstr;

}