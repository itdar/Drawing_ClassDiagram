//OnVScrollPageUp.cpp

#include "OnVScrollPageUp.h"
#include "ClassDiagramForm.h"
#include "ScrollMovingObject.h"

OnVScrollPageUp::OnVScrollPageUp() {
}
OnVScrollPageUp::OnVScrollPageUp(const OnVScrollPageUp& source) {
}
OnVScrollPageUp::~OnVScrollPageUp() {
}

void OnVScrollPageUp::Scrolling(ClassDiagramForm *classDiagramForm) {
	int minpos;
	int maxpos;
	classDiagramForm->GetScrollRange(SB_VERT, &minpos, &maxpos);
	maxpos = classDiagramForm->GetScrollLimit(SB_VERT);

	// Get the current position of scroll box.
	int curpos = classDiagramForm->GetScrollPos(SB_VERT);
	int newpos = curpos - 50;
	if (newpos < minpos) {
		newpos = minpos;
	}

	ScrollMovingObject moving;
	moving.MovingObject(classDiagramForm->diagram, 0, curpos-newpos);
	classDiagramForm->SetScrollPos(SB_VERT, newpos);

	bool ret;
	SCROLLINFO vScinfo;
	classDiagramForm->GetScrollInfo(SB_VERT, &vScinfo);
	//int vMax = vScinfo.nMax;
	int vMax = 2000 * classDiagramForm->zoomRate / 100;
	ret = moving.FindVertical(classDiagramForm->diagram, vScinfo.nPage);
	if (ret == false) {
		SCROLLINFO vScinfo;
		classDiagramForm->GetScrollInfo(SB_VERT, &vScinfo);
		vScinfo.nMax -= 50;
		if (vScinfo.nMax < vMax) {
			vScinfo.nMax = vMax;
		}
		if (vScinfo.nMax < vScinfo.nPage) {
			vScinfo.nMax = vScinfo.nPage;
		}
		classDiagramForm->SetScrollInfo(SB_VERT, &vScinfo);
	}

}