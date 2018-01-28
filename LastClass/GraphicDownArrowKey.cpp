//GraphicDownArrowKey.cpp

#include "GraphicDownArrowKey.h"
#include "ClassDiagramForm.h"
#include "TextEdit.h"
#include "OnVScrollLineDown.h"
#include "Selection.h"
#include "Diagram.h"
#include "SmartPointer.h"
#include "ArrayIterator.h"
#include "Class.h"
#include "Relation.h"

GraphicDownArrowKey::GraphicDownArrowKey() {
}

GraphicDownArrowKey::GraphicDownArrowKey(const GraphicDownArrowKey& source) {
}

GraphicDownArrowKey::~GraphicDownArrowKey() {
}

void GraphicDownArrowKey::KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc) {
	MovingVisitor movingVisitor;
	if (classDiagramForm->selection->GetLength() == 0) {
		OnVScrollLineDown onVScrollLineDown;
		onVScrollLineDown.Scrolling(classDiagramForm);
	}
	else if (classDiagramForm->selection->GetLength() == 1) {
		FigureComposite *object = static_cast<FigureComposite*>(classDiagramForm->selection->GetAt(0));
		CRect rect{ object->GetX() ,object->GetY() + 5, object->GetX() + object->GetWidth(),object->GetY() + object->GetHeight() + 5 };

			classDiagramForm->selection->Accept(classDiagramForm->diagram, movingVisitor, 0, 1);
		
	}
}


void GraphicDownArrowKey::KeyPress(TextEdit *textEdit) {
}