

//Association.h
// ¿¬°üÈ­

#ifndef _ASSOCIATION_H
#define _ASSOCIATION_H

#include "Relation.h"
#include "DrawingVisitor.h"

typedef signed long int Long;

class Association : public Relation {
public:
	Association(Long capacity = 10);
	Association(Long x, Long y, Long width, Long height);
	Association(const Association& source);
	virtual ~Association();

	Association& operator = (const Association&  source);
	void Accept(Visitor& visitor, CDC *pDC);
	Figure* Clone() const;

};
#endif // _ASSOCIATION_H