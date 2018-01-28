//ExitKeyMenuAction.cpp

#include "ExitKeyMenuAction.h"
#include "LastClass.h"

ExitKeyMenuAction::ExitKeyMenuAction() {
}

ExitKeyMenuAction::ExitKeyMenuAction(const ExitKeyMenuAction& source) {
}

ExitKeyMenuAction::~ExitKeyMenuAction() {
}

void ExitKeyMenuAction::MenuPress(LastClass *lastClass) {
	lastClass->OnClose();
}