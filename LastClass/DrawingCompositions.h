#ifndef _DRAWINGCOMPOSITIONS_H
#define _DRAWINGCOMPOSITIONS_H
#include "MouseLButtonAction.h"

class DrawingCompositions :public MouseLButtonAction {
public:
	static MouseLButtonAction* Instance();

	virtual void MouseLButtonUp(MouseLButton *mouseLButton, ClassDiagramForm *classDiagramForm, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY);
	virtual void MouseLButtonDown(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY);
	virtual void MouseLButtonDrag(MouseLButton *mouseLButton, ClassDiagramForm *classDiagramForm, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY, CDC *pDC);


protected:
	//DrawingClass();
private:
	static DrawingCompositions* instance;
};

#endif // !_DRAWINGCOMPOSITIONS_H

