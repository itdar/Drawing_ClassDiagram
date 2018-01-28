//TabKey.cpp

#include "TabKey.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "Caret.h"
#include "SingleByteCharacter.h"
#include "HistoryText.h"
#include "DeleteTextArea.h"
#include "ClassDiagramForm.h"

TabKey::TabKey() {
}

TabKey::TabKey(const TabKey& source) {
}

TabKey::~TabKey() {
}

void TabKey::KeyPress(TextEdit *textEdit) {
	if (textEdit->flagSelection == 1) {
		DeleteTextArea *deleteArea = new DeleteTextArea();
		deleteArea->DeleteArea(textEdit);
		if (deleteArea != 0) {
			delete deleteArea;
		}
	}

	SingleByteCharacter tab('\t');
	if (textEdit->caret->GetCharacterIndex() == textEdit->text->GetAt(textEdit->caret->GetRowIndex())->GetLength()) {
		textEdit->text->GetAt(textEdit->caret->GetRowIndex())->Add(tab.Clone());
	}
	else {
		textEdit->text->GetAt(textEdit->caret->GetRowIndex())->Insert(textEdit->caret->GetCharacterIndex(), tab.Clone());
	}
	textEdit->caret->MoveForwardCharacterIndex();
}

void TabKey::KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc) {
}