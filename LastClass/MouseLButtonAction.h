//MouseLButtonAction.h

#ifndef _MOUSELBUTTONACTION_H
#define _MOUSELBUTTONACTION_H

#include "MouseLButton.h"

class MouseLButton;
class ClassDiagramForm;
class Diagram;
class Selection;
typedef signed long int Long;

class MouseLButtonAction {
public:
	virtual void MouseLButtonUp(MouseLButton *mouseLButton, ClassDiagramForm *classDiagramForm, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) = 0;
	virtual void MouseLButtonDown(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) = 0;
	virtual void MouseLButtonDrag(MouseLButton *mouseLButton, ClassDiagramForm *classDiagramForm, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY, CDC *pDC) = 0;
protected:
	void ChangeState(MouseLButton* mouseLButton, MouseLButtonAction *mouseLButtonAction,UINT nChar=0);
	void ChangeDefault(MouseLButton* mouseLButton);
};
#endif // !_MOUSELBUTTONACTION_H

