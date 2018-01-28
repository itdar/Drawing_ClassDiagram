//AboutMenuAction.cpp

#include "AboutMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "AboutMenu.h"

AboutMenuAction::AboutMenuAction() {
}
AboutMenuAction::~AboutMenuAction() {
}
void AboutMenuAction::MenuPress(LastClass* lastClass) {
	CRect rect;
	lastClass->GetClientRect(&rect);
	AboutMenu *aboutMenu = new AboutMenu(lastClass);
	aboutMenu->Create(NULL, "정보", WS_CAPTION | WS_SYSMENU | WS_VISIBLE); //CFrameWnd 꺼 갖다쓰는듯??
	aboutMenu->ShowWindow(SW_SHOW);
	aboutMenu->UpdateWindow();
	//supportMenu->Create(NULL, "SupportMenu", WS_CHILD | WS_VISIBLE | WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, CRect(rect.CenterPoint().x - 450, rect.CenterPoint().y - 225 , rect.CenterPoint().x +450, rect.CenterPoint().y +225 ), lastClass, 10001, NULL);
	aboutMenu->SetFocus();
}