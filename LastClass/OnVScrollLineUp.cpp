//OnVScrollLineUp.cpp

#include "OnVScrollLineUp.h"
#include "ClassDiagramForm.h"
#include "ScrollMovingObject.h"

OnVScrollLineUp::OnVScrollLineUp() {
}
OnVScrollLineUp::OnVScrollLineUp(const OnVScrollLineUp& source) {
}
OnVScrollLineUp::~OnVScrollLineUp() {
}

void OnVScrollLineUp::Scrolling(ClassDiagramForm *classDiagramForm) {
	int minpos;
	int maxpos;
	bool ret;
	ScrollMovingObject moving;
	classDiagramForm->GetScrollRange(SB_VERT, &minpos, &maxpos);

	// Get the current position of scroll box.
	int curpos = classDiagramForm->GetScrollPos(SB_VERT);
	int newpos = curpos - 100;
	if (newpos < minpos) {
		newpos = minpos;
	}
	classDiagramForm->SetScrollPos(SB_VERT, newpos);
	moving.MovingObject(classDiagramForm->diagram, 0, curpos-newpos);


	SCROLLINFO vScinfo;
	classDiagramForm->GetScrollInfo(SB_VERT, &vScinfo);
	//int vMax = vScinfo.nMax;
	int vMax = 2000 * classDiagramForm->zoomRate / 100;
	ret = moving.FindVertical(classDiagramForm->diagram, vScinfo.nPage);
	if (ret == false) {
		SCROLLINFO vScinfo;
		classDiagramForm->GetScrollInfo(SB_VERT, &vScinfo);
		vScinfo.nMax -= 100;
		if (vScinfo.nMax < vMax) {
			vScinfo.nMax = vMax;
		}
		if (vScinfo.nMax < vScinfo.nPage) {
			vScinfo.nMax = vScinfo.nPage;
		}
		classDiagramForm->SetScrollInfo(SB_VERT, &vScinfo);
	}

}