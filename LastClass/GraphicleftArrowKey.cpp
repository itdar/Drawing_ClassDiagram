//GraphicLeftArrowKey.cpp

#include "GraphicLeftArrowKey.h"
#include "ClassDiagramForm.h"
#include "TextEdit.h"
#include "OnHScrollLineLeft.h"
#include "Selection.h"
#include "Diagram.h"
#include "SmartPointer.h"
#include "ArrayIterator.h"
#include "Class.h"
#include "Relation.h"


GraphicLeftArrowKey::GraphicLeftArrowKey() {
}

GraphicLeftArrowKey::GraphicLeftArrowKey(const GraphicLeftArrowKey& source) {
}

GraphicLeftArrowKey::~GraphicLeftArrowKey() {
}

void GraphicLeftArrowKey::KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc) {
	MovingVisitor movingVisitor;
	if (classDiagramForm->selection->GetLength() == 0) {
		OnHScrollLineLeft onHScrollLineLeft;
		onHScrollLineLeft.Scrolling(classDiagramForm);
	}
	else if (classDiagramForm->selection->GetLength() == 1) {
		FigureComposite *object = static_cast<FigureComposite*>(classDiagramForm->selection->GetAt(0));
		CRect rect{ object->GetX() - 5,object->GetY(), object->GetX() + object->GetWidth() - 5,object->GetY() + object->GetHeight() };
			classDiagramForm->selection->Accept(classDiagramForm->diagram, movingVisitor, -1, 0);
		
	}
}

void GraphicLeftArrowKey::KeyPress(TextEdit *textEdit) {
}