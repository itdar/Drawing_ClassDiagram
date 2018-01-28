#ifndef _SELECTION_H
#define _SELECTION_H
#include "FigureComposite.h"
#include "MovingVisitor.h"
#include "DrawingVisitor.h"
#include <afxwin.h>
using namespace std;
typedef signed long  int Long;
class Diagram;
class Selection : public  FigureComposite{
public: 
	Selection(Long capacity = 50000);
	Selection(const Selection& source);
	virtual ~Selection();
	Selection& operator = (const Selection& source);

	Long Remove(Diagram *diagram, Figure *figure);
	virtual Long Remove(Long index);
	virtual Long Add(Figure *figure);
	virtual Figure* GetAt(Long index);
	virtual Figure* Clone() const;
	void DeleteAllItems();
	void Accept(Diagram *diagram,Visitor& visitor, Long distanceX, Long distanceY);
	void Accept(Visitor& visitor, CDC *pDC);

	void SelectByArea(Diagram *diagram, CRect area);
	Long SelectByPoint(Diagram *diagram, Long x, Long y);
	Long SelectByPointForRelation(Diagram *diagram, Long x, Long y);
	Long SelectByPoint(Long x, Long y);
	Selection* MakeSelectionBuffer(Selection& selection);
	CPoint GetTopLeftPoint(Selection& selection);
	void DeleteOutSideRelation(Selection& selection);

	virtual Long Correct(Figure *figure, Long index);
	CRect GetSelectionRect(Selection& selection);

};

#endif // !_SELECTION_H
