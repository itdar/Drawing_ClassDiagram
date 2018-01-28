//SelfAggregations.h
#ifndef _SELFAGGREGATIONS_H
#define _SELFAGGREGATIONS_H

#include "SelfRelation.h"
#include "DrawingVisitor.h"

typedef signed long int Long;
class SelfAggregations :public SelfRelation {
public:
	SelfAggregations();
	SelfAggregations(Long x, Long y, Long width, Long height);
	SelfAggregations(const SelfAggregations& source);
	SelfAggregations& operator = (const SelfAggregations& source);

	virtual ~SelfAggregations();
	Figure* Clone() const;
	void Accept(Visitor& visitor, CDC *pDC);

};
#endif // !_SELFAGGREGATIONS_H
