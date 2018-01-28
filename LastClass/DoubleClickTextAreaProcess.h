//DoubleClickTextAreaProcess.h

#ifndef _DOUBLECLICKTEXTAREAPROCESS_H
#define _DOUBLECLICKTEXTAREAPROCESS_H

typedef signed long int Long;

class TextEdit;
class DoubleClickTextAreaProcess {
public:
	DoubleClickTextAreaProcess();
	DoubleClickTextAreaProcess(const DoubleClickTextAreaProcess& source);
	~DoubleClickTextAreaProcess();
public:
	Long DoubleClickStartIndex(TextEdit *textEdit);
	Long DoubleClickEndIndex(TextEdit *textEdit);
};

#endif // _DOUBLECLICKTEXTAREAPROCESS_H