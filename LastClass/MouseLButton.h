//MouseLButton.h

#ifndef _MOUSELUTTON_H
#define _MOUSELUTTON_H

#include <afxwin.h>
using namespace std;

class MouseLButtonAction;
class ClassDiagramForm;
class Diagram;
class Selection;
typedef signed long int Long;

class MouseLButton {
public:
	MouseLButton();
	//~MouseLButton();

	void MouseLButtonUp(MouseLButton *mouseLButton, ClassDiagramForm *classDiagramForm, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY);
	void MouseLButtonDown(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY);
	void MouseLButtonDrag(MouseLButton *mouseLButton, ClassDiagramForm *classDiagramForm, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY,CDC *pDC);
	void ChangeState(UINT nChar);

	void ChangeDrawingClassState();
	void ChangeDrawingMemoBoxState();

	void ChangeDrawingAggregationState();
	void ChangeDrawingAggregationsState();
	void ChangeDrawingAssociationState();
	void ChangeDrawingCompositionState();
	void ChangeDrawingCompositionsState();
	void ChangeDrawingDependencyState();
	void ChangeDrawingDirectedAssociationState();
	void ChangeDrawingGeneralizationState();
	void ChangeDrawingMemoLineState();
	void ChangeDrawingRealizationState();
	void ChangeSelectionState();
	void ChangeMultipleState();
	void ChangeDefault();



	UINT GetButtonState()const;
//private:
	friend class  MouseLButtonAction;
	
	void ChangeState(MouseLButtonAction *mouseLButtonAction, UINT nChar = 0);

private:
	MouseLButtonAction *state;
	UINT buttonState;
};
inline UINT MouseLButton::GetButtonState()const {
	return this->buttonState;
}
#endif
