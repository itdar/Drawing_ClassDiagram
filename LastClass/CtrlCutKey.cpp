//CtrlCutKey.cpp

#include "CtrlCutKey.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "Caret.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
#include "DeleteTextArea.h"
#include "ClassDiagramForm.h"

CtrlCutKey::CtrlCutKey() {
}
CtrlCutKey::CtrlCutKey(const CtrlCutKey& source) {
}
CtrlCutKey::~CtrlCutKey() {
}

void CtrlCutKey::KeyPress(TextEdit *textEdit) {
	if (textEdit->flagSelection == 1) {
		OpenClipboard(NULL);
		EmptyClipboard();
		size_t cbstr = (textEdit->copyBuffer.GetLength() + 1) * sizeof(TCHAR);
		HGLOBAL h = GlobalAlloc(GMEM_MOVEABLE, cbstr);
		memcpy_s(GlobalLock(h), cbstr, textEdit->copyBuffer.LockBuffer(), cbstr);
		GlobalUnlock(h);
		textEdit->copyBuffer.UnlockBuffer();
		UINT uniFormat = (sizeof(TCHAR) == sizeof(WCHAR)) ? CF_UNICODETEXT : CF_TEXT;
		if (::SetClipboardData(uniFormat, h) == NULL) {
		}
		CloseClipboard();

		DeleteTextArea *deleteArea = new DeleteTextArea();
		deleteArea->DeleteArea(textEdit);
		if (deleteArea != 0) {
			delete deleteArea;
		}
	}
}

void CtrlCutKey::KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc) {
}