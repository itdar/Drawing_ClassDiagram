//PreciseMoving.h

#ifndef _PRECISEMOVING_H
#define _PRECISEMOVING_H

typedef signed long int Long;

class PreciseMoving {
public:
	PreciseMoving();
	PreciseMoving(const PreciseMoving& source);
	~PreciseMoving();
public:
	void ConvertPoint(Long *x, Long *y, Long extent = 10);
};

#endif _PRECISEMOVING_H