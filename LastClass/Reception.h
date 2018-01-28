//Reception.h

#ifndef _RECEPTION_H
#define _RECEPTION_H

#include "Figure.h"
#include "DrawingVisitor.h"

typedef signed long int Long;
using namespace std;


class Visitor;
class Reception :public Figure {
public:
	Reception();
	Reception(const Reception& source);
	Reception(Long x, Long y, Long width, Long height, string content);
	Reception(Long x, Long y, Long width, Long height, Long minimumWidth, Long minimumHeight, string content);
	~Reception();

	Reception& operator = (const Reception& source);

	Figure* Clone() const;
	void Accept(Visitor& visitor, CDC *pDC);
};

#endif // !_RECEPTION_H