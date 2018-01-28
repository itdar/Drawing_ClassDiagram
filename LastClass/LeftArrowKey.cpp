//LeftArrowKey.cpp

#include "LeftArrowKey.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "Caret.h"
#include "ClassDiagramForm.h"

LeftArrowKey::LeftArrowKey() {
}

LeftArrowKey::LeftArrowKey(const LeftArrowKey& source) {
}

LeftArrowKey::~LeftArrowKey() {
}

void LeftArrowKey::KeyPress(TextEdit *textEdit) {
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
	textEdit->caret->MoveBackwardCharacterIndex();
	if (textEdit->caret->GetCharacterIndex() < 0
		&& textEdit->caret->GetRowIndex() == 0) {
		textEdit->caret->MoveForwardCharacterIndex();
	}
	else if (textEdit->caret->GetCharacterIndex() < 0
		&& textEdit->caret->GetRowIndex() > 0) {
		textEdit->caret->MoveBackwardRowIndex();
		textEdit->caret->SetCharacterIndex(textEdit->text->GetAt(textEdit->caret->GetRowIndex())->GetLength());
	}
}

void LeftArrowKey::KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc) {
}