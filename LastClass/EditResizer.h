//EditResizer.h

#ifndef _EDITRESIZER_H
#define _EDITRESIZER_H

#include <afxwin.h>

class TextEdit;
class EditResizer {
public:
	EditResizer();
	EditResizer(const EditResizer& source);
	~EditResizer();
public:
	void ResizeEdit(TextEdit *textEdit, CDC *cdc);
	void ResizeClass(TextEdit *textEdit, CDC *cdc);
};

#endif // !_EDITRESIZER_H
