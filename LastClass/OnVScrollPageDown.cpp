//OnVScrollPageDown.cpp

#include "OnVScrollPageDown.h"
#include "ClassDiagramForm.h"
#include "ScrollMovingObject.h"

OnVScrollPageDown::OnVScrollPageDown() {
}
OnVScrollPageDown::OnVScrollPageDown(const OnVScrollPageDown& source) {
}
OnVScrollPageDown::~OnVScrollPageDown() {
}

void OnVScrollPageDown::Scrolling(ClassDiagramForm *classDiagramForm) {
	int minpos;
	int maxpos;
	classDiagramForm->GetScrollRange(SB_VERT, &minpos, &maxpos);
	maxpos = classDiagramForm->GetScrollLimit(SB_VERT);

	// Get the current position of scroll box.
	int curpos = classDiagramForm->GetScrollPos(SB_VERT);

	int newpos = curpos + 50;
	if (newpos > maxpos) {
		SCROLLINFO vScinfo;
		classDiagramForm->GetScrollInfo(SB_VERT, &vScinfo);
		vScinfo.nMax = newpos + vScinfo.nPage;
		classDiagramForm->SetScrollInfo(SB_VERT, &vScinfo);
	}
	ScrollMovingObject moving;
	moving.MovingObject(classDiagramForm->diagram, 0, curpos-newpos);
	classDiagramForm->SetScrollPos(SB_VERT, newpos);
}