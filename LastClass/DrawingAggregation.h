#ifndef _DRAWINGAGGREGATION_H
#define _DRAWINGAGGREGATION_H
#include "MouseLButtonAction.h"

class DrawingAggregation :public MouseLButtonAction {
public:
	static MouseLButtonAction* Instance();

	virtual void MouseLButtonUp(MouseLButton *mouseLButton, ClassDiagramForm *classDiagramForm, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY);
	virtual void MouseLButtonDown(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY);
	virtual void MouseLButtonDrag(MouseLButton *mouseLButton, ClassDiagramForm *classDiagramForm, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY, CDC *pDC);


protected:
	//DrawingClass();
private:
	static DrawingAggregation* instance;
};

#endif // !_DRAWINGAGGREGATION_H

