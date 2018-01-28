
//MemoBox.h
#ifndef _MEMOBOX_H
#define _MEMOBOX_H

#include "FigureComposite.h"
#include "DrawingVisitor.h"
typedef signed long int Long;

class MemoBox : public FigureComposite {
public:
	MemoBox(Long capacity = 10);
	MemoBox(Long x, Long y, Long width, Long height);
	MemoBox(Long x, Long y, Long width, Long height, Long minimumWidth, Long minimumHeight);
	MemoBox(const MemoBox& source);
	virtual ~MemoBox();	// 

	Long Add(Long x, Long y, Long width, Long height);	//
	virtual Long Add(Figure *figure);	//
	virtual Figure* GetAt(Long index);	//
	virtual Figure* Clone() const;	//
	virtual Long Remove(Long index);	//
	virtual Long Correct(Long index, Figure *figure);

	MemoBox& operator=(const MemoBox& source);
	Figure* operator[](Long index);


	void Accept(Visitor& visitor, CDC *pDC);
	void Accept(Visitor& visitor, Long distanceX, Long distanceY);
};

#endif // !_MEMOBOX_H

