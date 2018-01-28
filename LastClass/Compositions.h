
#ifndef _COMPOSITIONS_H
#define _COMPOSITIONS_H


#include "Relation.h"
#include "DrawingVisitor.h"

typedef signed long int Long;
class Compositions : public Relation {
public:
	Compositions(Long capacity = 10);
	Compositions(Long x, Long y, Long width, Long height);
	Compositions(const Compositions& source);
	virtual ~Compositions();

	Compositions& operator = (const Compositions&  source);
	void Accept(Visitor& visitor, CDC *pDC);
	Figure* Clone() const;

};
#endif // !_COMPOSITIONS_H
