//InsertKey.cpp

#include "InsertKey.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "ClassDiagramForm.h"

InsertKey::InsertKey() {
}

InsertKey::InsertKey(const InsertKey& source) {
}

InsertKey::~InsertKey() {
}

void InsertKey::KeyPress(TextEdit *textEdit) {
	if (textEdit->flagInsert == 1) {
		textEdit->flagInsert = 0;
	}
	else {
		textEdit->flagInsert = 1;
	}
}

void InsertKey::KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc) {
}