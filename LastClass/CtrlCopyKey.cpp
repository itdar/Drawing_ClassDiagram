//CtrlCopyKey.cpp

#include "CtrlCopyKey.h"
#include "TextEdit.h"
#include "ClassDiagramForm.h"

CtrlCopyKey::CtrlCopyKey() {
}
CtrlCopyKey::CtrlCopyKey(const CtrlCopyKey& source) {
}
CtrlCopyKey::~CtrlCopyKey() {
}

void CtrlCopyKey::KeyPress(TextEdit *textEdit) {
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
}

void CtrlCopyKey::KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc) {
}