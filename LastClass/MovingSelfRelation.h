//MovingSelfRelation.h

#ifndef _MOVINGSELFRELATION_H
#define _MOVINGSELFRELATION_H

#include "MouseLButtonAction.h"


class MovingSelfRelation :public MouseLButtonAction {
public:
	static MouseLButtonAction* Instance();

	virtual void MouseLButtonUp(MouseLButton *mouseLButton, ClassDiagramForm *classDiagramForm, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY);
	virtual void MouseLButtonDown(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY);
	virtual void MouseLButtonDrag(MouseLButton *mouseLButton, ClassDiagramForm *classDiagramForm, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY, CDC *pDC);
protected:

private:
	static MovingSelfRelation* instance;
};
#endif // !_MOVINGSELFRELATION_H


