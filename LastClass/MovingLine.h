//MovingLine.h

#ifndef _MOVINGLINE_H
#define _MOVINGLINE_H

#include "MouseLButtonAction.h"


class MovingLine :public MouseLButtonAction {
public:
	static MouseLButtonAction* Instance();

	virtual void MouseLButtonUp(MouseLButton *mouseLButton, ClassDiagramForm *classDiagramForm, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY);
	virtual void MouseLButtonDown(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY);
	virtual void MouseLButtonDrag(MouseLButton *mouseLButton, ClassDiagramForm *classDiagramForm, Diagram *diagram, Selection *selection,Long  startX, Long startY, Long currentX, Long currentY, CDC *pDC);
protected:
	//DrawingClass();
private:
	static MovingLine* instance;
};
#endif // !_MOVINGLINE_H