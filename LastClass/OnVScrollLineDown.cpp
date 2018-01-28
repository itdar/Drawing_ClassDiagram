//OnVScrollLineDown.cpp

#include "OnVScrollLineDown.h"
#include "ClassDiagramForm.h"
#include "ScrollMovingObject.h"

OnVScrollLineDown::OnVScrollLineDown() {
}
OnVScrollLineDown::OnVScrollLineDown(const OnVScrollLineDown& source) {
}
OnVScrollLineDown::~OnVScrollLineDown() {
}

void OnVScrollLineDown::Scrolling(ClassDiagramForm *classDiagramForm) {
	int minpos;
	int maxpos;
	classDiagramForm->GetScrollRange(SB_VERT, &minpos, &maxpos);
	maxpos = classDiagramForm->GetScrollLimit(SB_VERT);

	// Get the current position of scroll box.
	int curpos = classDiagramForm->GetScrollPos(SB_VERT);

	curpos += 100;
	if (curpos > maxpos) {
		SCROLLINFO vScinfo;
		classDiagramForm->GetScrollInfo(SB_VERT, &vScinfo);
		vScinfo.nMax = curpos + vScinfo.nPage;
		classDiagramForm->SetScrollInfo(SB_VERT, &vScinfo);
	}
	//if (curpos != maxpos) {
		ScrollMovingObject moving;
		moving.MovingObject(classDiagramForm->diagram, 0, -100);
	//}
	classDiagramForm->SetScrollPos(SB_VERT, curpos);
}