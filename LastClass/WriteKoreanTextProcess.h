//WriteKoreanTextProcess.h

#ifndef _WRITEKOREANTEXTPROCESS_H
#define _WRITEKOREANTEXTPROCESS_H

typedef signed long int Long;

class TextEdit;
class WriteKoreanTextProcess {
public:
	WriteKoreanTextProcess();
	WriteKoreanTextProcess(const WriteKoreanTextProcess& source);
	~WriteKoreanTextProcess();
public:
	void EndComposition(TextEdit *textEdit, Long bufferLength, char (*buffer));
	void StartComposition(TextEdit *textEdit, Long bufferLength, char (*buffer));
	void DuringComposition(TextEdit *textEdit, Long bufferLength, char (*buffer));
};

#endif // _WRITEKOREATEXTPROCESS_H