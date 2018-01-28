// MinusKey.cpp

#include "MinusKey.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "Caret.h"
#include "ClassDiagramForm.h"

MinusKey::MinusKey() {
}

MinusKey::MinusKey(const MinusKey& source) {
}

MinusKey::~MinusKey() {
}

void MinusKey::KeyPress(TextEdit *textEdit) {
	textEdit->rowHeight--;
}

void MinusKey::KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc) {
}