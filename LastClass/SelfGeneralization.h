//SelfGeneralization.h
#ifndef _SELFGENERALIZATION_H
#define _SELFGENERALIZATION_H

#include "SelfRelation.h"
#include "DrawingVisitor.h"

typedef signed long int Long;
class SelfGeneralization :public SelfRelation {
public:
	SelfGeneralization();
	SelfGeneralization(Long x, Long y, Long width, Long height);
	SelfGeneralization(const SelfGeneralization& source);
	SelfGeneralization& operator = (const SelfGeneralization& source);

	virtual ~SelfGeneralization();
	Figure* Clone() const;
	void Accept(Visitor& visitor, CDC *pDC);

};
#endif // !_SELFGENERALIZATION_H
