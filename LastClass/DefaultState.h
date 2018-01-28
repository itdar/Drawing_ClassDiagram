//DefaultState.h

#ifndef _DEFAULTSTATE_H
#define _DEFAULTSTATE_H

#include "MouseLButtonAction.h"


class DefaultState :public MouseLButtonAction {
public:
	static MouseLButtonAction* Instance();

	virtual void MouseLButtonUp(MouseLButton *mouseLButton, ClassDiagramForm *classDiagramForm, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY);
	virtual void MouseLButtonDown(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY);
	virtual void MouseLButtonDrag(MouseLButton *mouseLButton, ClassDiagramForm *classDiagramForm, Diagram *diagram, Selection *selection,Long  startX, Long startY, Long currentX, Long currentY, CDC *pDC);
protected:
	//DrawingClass();
private:
	static DefaultState* instance;
};
#endif // !_DEFAULTSTATE_H

