//EndKey.cpp

#include "EndKey.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "Figure.h"
#include "Caret.h"
#include "KeyBoard.h"
#include <afxwin.h>
#include "ClassDiagramForm.h"

EndKey::EndKey() {
}
EndKey::EndKey(const EndKey& source) {
}
EndKey::~EndKey() {
}
void EndKey::KeyPress(TextEdit *textEdit) {
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
	textEdit->caret->SetCharacterIndex(textEdit->text->GetAt(textEdit->caret->GetRowIndex())->GetLength());
}

void EndKey::KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc) {
}