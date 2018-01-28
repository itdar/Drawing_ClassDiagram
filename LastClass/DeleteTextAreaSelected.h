//DeleteTextAreaSelected.h

#ifndef _DELETETEXTAREASELECTED_H
#define _DELETETEXTAREASELECTED_H

typedef signed long int Long;

class TextEdit;
class DeleteTextAreaSelected {
public:
	DeleteTextAreaSelected();
	DeleteTextAreaSelected(const DeleteTextAreaSelected& source);
	~DeleteTextAreaSelected();
public:
	void DeleteSingleLineSelected(TextEdit *textEdit);
	void DeleteFirstMultiLineSelected(TextEdit *textEdit);
	void DeleteMiddleMultiLineSelected(TextEdit *textEdit);
	void DeleteEndMultiLineSelected(TextEdit *textEdit);
	void ConnectRemains(TextEdit *textEdit, Long copyCount);
};

#endif //_DELETETEXTAREASELECTED_H