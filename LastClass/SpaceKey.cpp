//SpaceKey.cpp

#include "SpaceKey.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "Caret.h"
#include "SingleByteCharacter.h"
#include "HistoryText.h"
#include "TextAreaSelected.h"
#include "DeleteTextArea.h"
#include "ClassDiagramForm.h"
SpaceKey::SpaceKey() {
}

SpaceKey::SpaceKey(const SpaceKey& source) {
}

SpaceKey::~SpaceKey() {
}

void SpaceKey::KeyPress(TextEdit *textEdit) {
	if (textEdit->flagSelection == 1) {
		DeleteTextArea *deleteArea = new DeleteTextArea();
		deleteArea->DeleteArea(textEdit);
		if (deleteArea != 0) {
			delete deleteArea;
		}
	}
	SingleByteCharacter spaceText(' ');
	textEdit->text->GetAt(textEdit->caret->GetRowIndex())->Insert(textEdit->caret->GetCharacterIndex(), spaceText.Clone());
	textEdit->caret->MoveForwardCharacterIndex();
}

void SpaceKey::KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc) {
}