//GraphicUpArrowKey.cpp

#include "GraphicUpArrowKey.h"
#include "ClassDiagramForm.h"
#include "TextEdit.h"
#include "OnVScrollLineUp.h"
#include "Selection.h"
#include "Diagram.h"
#include "SmartPointer.h"
#include "ArrayIterator.h"
#include "Class.h"
#include "Relation.h"

GraphicUpArrowKey::GraphicUpArrowKey() {
}

GraphicUpArrowKey::GraphicUpArrowKey(const GraphicUpArrowKey& source) {
}

GraphicUpArrowKey::~GraphicUpArrowKey() {
}

void GraphicUpArrowKey::KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc) {
	MovingVisitor movingVisitor;
	if (classDiagramForm->selection->GetLength() == 0) {
		OnVScrollLineUp onVScrollLineUp;
		onVScrollLineUp.Scrolling(classDiagramForm);
	}
	else if (classDiagramForm->selection->GetLength() == 1) {
		FigureComposite *object = static_cast<FigureComposite*>(classDiagramForm->selection->GetAt(0));
		CRect rect{ object->GetX() ,object->GetY() - 5, object->GetX() + object->GetWidth(),object->GetY() + object->GetHeight() - 5 };
		
			classDiagramForm->selection->Accept(classDiagramForm->diagram, movingVisitor, 0, -1);
	}
}


void GraphicUpArrowKey::KeyPress(TextEdit *textEdit) {
}