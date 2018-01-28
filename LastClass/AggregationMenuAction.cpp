#include "AggregationMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "MouseLButton.h"
AggregationMenuAction::AggregationMenuAction() {
}
AggregationMenuAction::~AggregationMenuAction() {
}
void AggregationMenuAction::MenuPress(LastClass* lastClass) {
	if (lastClass->classDiagramForm->textEdit == 0) {
		lastClass->classDiagramForm->mouseLButton->ChangeDrawingAggregationState();
	}
}