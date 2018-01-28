//OnVScrollBottom.cpp

#include "OnVScrollBottom.h"
#include "ClassDiagramForm.h"

OnVScrollBottom::OnVScrollBottom() {
}
OnVScrollBottom::OnVScrollBottom(const OnVScrollBottom& source) {
}
OnVScrollBottom::~OnVScrollBottom() {
}

void OnVScrollBottom::Scrolling(ClassDiagramForm *classDiagramForm) {
	int minpos;
	int maxpos;
	classDiagramForm->GetScrollRange(SB_VERT, &minpos, &maxpos);
	maxpos = classDiagramForm->GetScrollLimit(SB_VERT);

	// Get the current position of scroll box.
	int curpos = classDiagramForm->GetScrollPos(SB_VERT);

	curpos = maxpos;

	classDiagramForm->SetScrollPos(SB_VERT, curpos);
}