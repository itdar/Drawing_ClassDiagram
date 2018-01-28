//SelfAssociation.h
#ifndef _SELFASSOCIATION_H
#define _SELFASSOCIATION_H

#include "SelfRelation.h"
#include "DrawingVisitor.h"

typedef signed long int Long;
class SelfAssociation :public SelfRelation {
public:
	SelfAssociation();
	SelfAssociation(Long x, Long y, Long width, Long height);
	SelfAssociation(const SelfAssociation& source);
	SelfAssociation& operator = (const SelfAssociation& source);

	virtual ~SelfAssociation();
	Figure* Clone() const;
	void Accept(Visitor& visitor, CDC *pDC);

};
#endif // !_SELFASSOCIATION_H
