
//MemoLine.h
// ¸Þ¸ð¼±

#ifndef _MemoLine_H
#define _MemoLine_H

#include "Relation.h"
#include "DrawingVisitor.h"

typedef signed long int Long;

class MemoLine : public Relation {
public:
	MemoLine(Long capacity = 10);
	MemoLine(Long x, Long y, Long width, Long height);
	MemoLine(const MemoLine& source);
	virtual ~MemoLine();

	MemoLine& operator = (const MemoLine&  source);
	void Accept(Visitor& visitor, CDC *pDC);
	Figure* Clone() const;

};
#endif //  _MemoLine_H