//GraphicRightArrowKey.cpp

#include "GraphicRightArrowKey.h"
#include "ClassDiagramForm.h"
#include "TextEdit.h"
#include "OnHScrollLineRight.h"
#include "Selection.h"
#include "Diagram.h"
#include "SmartPointer.h"
#include "ArrayIterator.h"
#include "Class.h"
#include "Relation.h"

GraphicRightArrowKey::GraphicRightArrowKey() {
}

GraphicRightArrowKey::GraphicRightArrowKey(const GraphicRightArrowKey& source) {
}

GraphicRightArrowKey::~GraphicRightArrowKey() {
}

void GraphicRightArrowKey::KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc) {
	MovingVisitor movingVisitor;
	if (classDiagramForm->selection->GetLength() == 0) {
		OnHScrollLineRight onHScrollLineRight;
		onHScrollLineRight.Scrolling(classDiagramForm);
	}
	else if (classDiagramForm->selection->GetLength() == 1) {
		FigureComposite *object = static_cast<FigureComposite*>(classDiagramForm->selection->GetAt(0));
		CRect rect{ object->GetX() + 5,object->GetY(), object->GetX() + object->GetWidth() + 5,object->GetY() + object->GetHeight() };
		classDiagramForm->selection->Accept(classDiagramForm->diagram, movingVisitor, 1, 0);
		
	}
}

void GraphicRightArrowKey::KeyPress(TextEdit *textEdit) {
}