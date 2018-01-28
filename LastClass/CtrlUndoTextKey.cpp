//CtrlUndoTextKey.cpp

#include "CtrlUndoTextKey.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "Caret.h"
#include "HistoryText.h"
#include "ClassDiagramForm.h"

CtrlUndoTextKey::CtrlUndoTextKey() {
}
CtrlUndoTextKey::CtrlUndoTextKey(const CtrlUndoTextKey& source) {
}
CtrlUndoTextKey::~CtrlUndoTextKey() {
}

void CtrlUndoTextKey::KeyPress(TextEdit *textEdit) {
	if (textEdit->historyText->undoTextArray->GetLength() > 0) {
		Text *text_ = textEdit->historyText->PopUndoText();
		Caret *caret_ = textEdit->historyText->PopUndoCaret();

		Text *tempText = new Text(*(textEdit->text));
		Caret *tempCaret = new Caret(*(textEdit->caret));
		textEdit->historyText->PushRedo(tempText, tempCaret);

		delete[] textEdit->text;
		textEdit->text = text_;
		delete textEdit->caret;
		textEdit->caret = caret_;
	}
}

void CtrlUndoTextKey::KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc) {
}