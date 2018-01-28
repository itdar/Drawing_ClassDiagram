//CtrlRedoTextKey.cpp

#include "CtrlRedoTextKey.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "Caret.h"
#include "HistoryText.h"
#include "ClassDiagramForm.h"

CtrlRedoTextKey::CtrlRedoTextKey() {
}
CtrlRedoTextKey::CtrlRedoTextKey(const CtrlRedoTextKey& source) {
}
CtrlRedoTextKey::~CtrlRedoTextKey() {
}

void CtrlRedoTextKey::KeyPress(TextEdit *textEdit) {
	if (textEdit->historyText->redoTextArray->GetLength() > 0) {
		Text *text_ = textEdit->historyText->PopRedoText();
		Caret *caret_ = textEdit->historyText->PopRedoCaret();

		Text *tempText = new Text(*(textEdit->text));
		Caret *tempCaret = new Caret(*(textEdit->caret));
		textEdit->historyText->PushUndo(tempText, tempCaret);

		delete[] textEdit->text;
		textEdit->text = text_;
		delete textEdit->caret;
		textEdit->caret = caret_;
	}
}

void CtrlRedoTextKey::KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc) {
}