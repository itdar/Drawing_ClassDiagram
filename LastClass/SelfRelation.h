//SelfRelation.h

#ifndef _SELFRELATION_H
#define _SELFRELATION_H

#include "Array.h"
#include "Figure.h"

#include <afxwin.h>

typedef signed long int Long;

class Visitor;
class SelfRelation :public Figure {
public:
	SelfRelation();
	SelfRelation(Long x, Long y, Long width, Long height);
	SelfRelation(const SelfRelation& source);
	virtual ~SelfRelation() = 0;
	SelfRelation& operator =(const SelfRelation& source);
	void ReplaceString(string rollNameText, Long rollNameBoxIndex);
	void Accept(Visitor& visitor, CDC *cPaintDc);
	Figure* Clone()const = 0;
public:
	Long leftRightFlag;
	Array<string>* rollNames;
	Array<CPoint>* rollNamePoints;
};

#endif // !_SELFRELATION_H

