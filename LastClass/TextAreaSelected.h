//TextAreaSelected.h

#ifndef _TEXTAREASELECTED_H
#define _TEXTAREASELECTED_H

#include <afxwin.h>

typedef signed long int Long;

class TextAreaSelectedProcess;
class TextEdit;
class TextAreaSelected {
public:
	TextAreaSelected();
	TextAreaSelected(const TextAreaSelected& source);
	~TextAreaSelected();

	void SelectTextArea(TextEdit *textEdit, CDC *pDC);
public:
	TextAreaSelectedProcess *selected;
};

#endif //_TEXTAREASELECTED_H