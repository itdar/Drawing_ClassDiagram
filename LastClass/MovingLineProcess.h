//MovingLineProcess.h

#ifndef _MOVINGLINEPROCESS_H
#define _MOVINGLINEPROCESS_H

typedef signed long int Long;

class Class;
class MovingLineProcess {
public:
	static MovingLineProcess* Instance();
public:
	MovingLineProcess();
	MovingLineProcess(const MovingLineProcess& source);
	~MovingLineProcess();
public:
	void MoveUpAttributeLine(Class *selectedClass, Long  startX, Long startY, Long currentX, Long currentY);
	void MoveUpMethodLine(Class *selectedClass, Long  startX, Long startY, Long currentX, Long currentY);
	void MoveUpReception(Class *selectedClass, Long  startX, Long startY, Long currentX, Long currentY);

	void MoveDownAttributeLine(Class *selectedClass, Long  startX, Long startY, Long currentX, Long currentY);
	void MoveDownMethodLine(Class *selectedClass, Long  startX, Long startY, Long currentX, Long currentY);
	void MoveDownReception(Class *selectedClass, Long  startX, Long startY, Long currentX, Long currentY);
private:
	static MovingLineProcess* instance;
};

#endif // _MOVINGLINEPROCESS_H