//OnVScrollTop.cpp

#include "OnVScrollTop.h"
#include "ClassDiagramForm.h"

OnVScrollTop::OnVScrollTop() {
}
OnVScrollTop::OnVScrollTop(const OnVScrollTop& source) {
}
OnVScrollTop::~OnVScrollTop() {
}

void OnVScrollTop::Scrolling(ClassDiagramForm *classDiagramForm) {
	int minpos;
	int maxpos;
	classDiagramForm->GetScrollRange(SB_VERT, &minpos, &maxpos);
	maxpos = classDiagramForm->GetScrollLimit(SB_VERT);

	// Get the current position of scroll box.
	int curpos = classDiagramForm->GetScrollPos(SB_VERT);

	curpos = minpos;

	classDiagramForm->SetScrollPos(SB_VERT, curpos);
}