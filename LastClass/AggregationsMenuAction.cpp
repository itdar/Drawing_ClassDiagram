#include "AggregationsMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "MouseLButton.h"
AggregationsMenuAction::AggregationsMenuAction() {
}
AggregationsMenuAction::~AggregationsMenuAction() {
}
void AggregationsMenuAction::MenuPress(LastClass* lastClass) {
	if (lastClass->classDiagramForm->textEdit == 0) {
		lastClass->classDiagramForm->mouseLButton->ChangeDrawingAggregationsState();
	}
}