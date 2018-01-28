#include "SupportMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "SupportMenu.h"

SupportMenuAction::SupportMenuAction() {
}
SupportMenuAction::~SupportMenuAction() {
}
void SupportMenuAction::MenuPress(LastClass* lastClass) {
	SupportMenu *supportMenu = new SupportMenu(lastClass);
	supportMenu->Create(NULL, "도  움  말", WS_CAPTION | WS_SYSMENU | WS_VISIBLE); //CFrameWnd 꺼 갖다쓰는듯??
	supportMenu->ShowWindow(SW_SHOW);
	supportMenu->UpdateWindow();
	//supportMenu->Create(NULL, "SupportMenu", WS_CHILD | WS_VISIBLE | WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, CRect(rect.CenterPoint().x - 450, rect.CenterPoint().y - 225 , rect.CenterPoint().x +450, rect.CenterPoint().y +225 ), lastClass, 10001, NULL);
	supportMenu->SetFocus();
}