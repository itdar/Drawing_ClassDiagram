
//Aggregation.h
//С§Че

#ifndef _AGGREGATION_H
#define _AGGREGATION_H

#include "Relation.h"
#include "DrawingVisitor.h"

typedef signed long int Long;

class Aggregation : public Relation {
public:
	Aggregation(Long capacity = 10);
	Aggregation(Long x, Long y, Long width, Long height);
	Aggregation(const Aggregation& source);
	virtual ~Aggregation();

	Aggregation& operator = (const Aggregation&  source);
	void Accept(Visitor& visitor, CDC *pDC);
	Figure* Clone() const;

};
#endif // _AGGREGATION_H