//RightArrowKey.cpp

#include "RightArrowKey.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "Caret.h"
#include "ClassDiagramForm.h"

RightArrowKey::RightArrowKey() {
}

RightArrowKey::RightArrowKey(const RightArrowKey& source) {
}

RightArrowKey::~RightArrowKey() {
}

void RightArrowKey::KeyPress(TextEdit *textEdit) {
	if (GetKeyState(VK_SHIFT) >= 0) {
		if (textEdit->flagSelection == 1) {
			textEdit->flagSelection = 0;
		}
	}
	else {
		if (textEdit->flagSelection == 0) {
			textEdit->flagSelection = 1;
			textEdit->selectedX = textEdit->caret->GetCharacterIndex();
			textEdit->selectedY = textEdit->caret->GetRowIndex();
		}
	}
	textEdit->caret->MoveForwardCharacterIndex();
	if (textEdit->caret->GetCharacterIndex() > textEdit->text->GetAt(textEdit->caret->GetRowIndex())->GetLength()
		&& textEdit->caret->GetRowIndex() == textEdit->text->GetLength() - 1) {
		textEdit->caret->MoveBackwardCharacterIndex();
	}
	else if (textEdit->caret->GetCharacterIndex() > textEdit->text->GetAt(textEdit->caret->GetRowIndex())->GetLength()
		&& textEdit->caret->GetRowIndex() < textEdit->text->GetLength() - 1) {
		textEdit->caret->SetCharacterIndex(0);
		textEdit->caret->MoveForwardRowIndex();
	}
}

void RightArrowKey::KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc) {
}