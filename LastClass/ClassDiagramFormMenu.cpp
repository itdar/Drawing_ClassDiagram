#include "ClassDiagramFormMenu.h"
#include "ClassDiagramForm.h"
#include "MenuAction.h"
#include "ClassMenuAction.h"
#include "MemoBoxMenuAction.h"
#include "GeneralizationMenuAction.h"
#include "RealizationMenuAction.h"
#include "DependencyMenuAction.h"
#include "AssociationMenuAction.h"
#include "DirectedAssociationMenuAction.h"
#include "AggregationMenuAction.h"
#include "AggregationsMenuAction.h"
#include "CompositionMenuAction.h"
#include "CompositionsMenuAction.h"
#include "MemoLineMenuAction.h"
#include "GraphicCtrlUndoMenuAction.h"
#include "GraphicCtrlCutMenuAction.h"
#include "GraphicCtrlCopyMenuAction.h"
#include "GraphicCtrlPasteMenuAction.h"
#include "AddTemplateMenuAction.h"
#include "DeleteTemplateMenuAction.h"
#include "DeleteMenuAction.h"
#include "AddAttributeMenuAction.h"
#include "DeleteAttributeMenuAction.h"
#include "AddMethodMenuAction.h"
#include "DeleteMethodMenuAction.h"
#include "AddReceptionMenuAction.h"
#include "DeleteReceptionMenuAction.h"
#include "GraphicCtrlRedoMenuAction.h"

ClassDiagramFormMenu::ClassDiagramFormMenu(ClassDiagramForm* classDiagramForm) {
	this->classDiagramForm = classDiagramForm;
	this->menu1 = new CMenu;  //선택된게 없을때 
	this->drawMenu = new CMenu; // 그리기 메뉴

	this->menu2 = new CMenu; // 선택된게 1개
	this->menu3 = new CMenu;
	
	
//////////////////////////////////////////////////////////////////////
	this->menu1->CreatePopupMenu();
	this->drawMenu->CreatePopupMenu();
	//this->undoMenu->CreatePopupMenu(); 없어도 되는지
//////////////////////////////////////////////////////////////////////
	this->menu2->CreatePopupMenu();
	this->menu3->CreatePopupMenu();
//////////////////////////////////////////////////////////////////////////
	this->menu1->AppendMenu(MF_STRING, 123, "되돌리기(Z)");
	this->menu1->AppendMenu(MF_STRING, 136, "재실행(Y)");
	this->menu1->AppendMenu(MF_STRING, 108, "붙여넣기(V)");
	this->menu1->AppendMenu(MF_SEPARATOR);
	this->menu1->AppendMenu(MF_POPUP, (UINT_PTR)this->drawMenu->m_hMenu, "그리기(D)");
	classDiagramForm->SetMenu(this->menu1);
	this->drawMenu->AppendMenu(MF_STRING, 110, "클래스 그리기");
	this->drawMenu->AppendMenu(MF_STRING, 112, "일반화(1)");
	this->drawMenu->AppendMenu(MF_STRING, 113, "실체화(2)");
	this->drawMenu->AppendMenu(MF_STRING, 114, "의존(3)");
	this->drawMenu->AppendMenu(MF_STRING, 115, "연관(4)");
	this->drawMenu->AppendMenu(MF_STRING, 116, "직접연관(5)");
	this->drawMenu->AppendMenu(MF_STRING, 117, "집합(6)");
	this->drawMenu->AppendMenu(MF_STRING, 118, "집합연관(7)");
	this->drawMenu->AppendMenu(MF_STRING, 119, "합성(8)");
	this->drawMenu->AppendMenu(MF_STRING, 120, "복합연관(9)");
	this->drawMenu->AppendMenu(MF_STRING, 111, "메모박스 그리기");
	this->drawMenu->AppendMenu(MF_STRING, 121, "메모라인(0)");
	///////////////////////////////////////////////////////////////////
	this->menu2->AppendMenu(MF_STRING, 109, "자르기(X)");
	this->menu2->AppendMenu(MF_SEPARATOR);
	this->menu2->AppendMenu(MF_STRING, 107, "복사하기(C)");
	this->menu2->AppendMenu(MF_STRING, 108, "붙여넣기(V)");
	this->menu2->AppendMenu(MF_STRING, 129, "삭제하기(D)");
	this->menu2->AppendMenu(MF_SEPARATOR);
	this->menu2->AppendMenu(MF_STRING, 127, "템플릿 추가");
	this->menu2->AppendMenu(MF_STRING, 135, "속성 추가");
	this->menu2->AppendMenu(MF_STRING, 130, "연산 추가");
	this->menu2->AppendMenu(MF_STRING, 133, "리셉션 추가");
	this->menu2->AppendMenu(MF_SEPARATOR);
	this->menu2->AppendMenu(MF_STRING, 128, "템플릿 제거");
	this->menu2->AppendMenu(MF_STRING, 131, "속성 제거");
	this->menu2->AppendMenu(MF_STRING, 132, "연산 제거");
	this->menu2->AppendMenu(MF_STRING, 134, "리셉션 제거");
/////////////////////////////////////////////////////////////////////////
	//this->menu3->AppendMenu(MF_STRING, 123, "되돌리기(Z)");
	//this->menu3->AppendMenu(MF_STRING, 136, "재실행(Y)");
	//this->menu3->AppendMenu(MF_SEPARATOR);
	this->menu3->AppendMenu(MF_STRING, 109, "자르기(X)");
	this->menu3->AppendMenu(MF_STRING, 107, "복사하기(C)");

}

ClassDiagramFormMenu::ClassDiagramFormMenu(const ClassDiagramFormMenu& source) {
	this->menu1 = source.menu1;
	this->drawMenu = source.drawMenu;
}

MenuAction* ClassDiagramFormMenu::MenuSelected(UINT parm_control_id) {
	if (this->menuAction != 0) {
		delete this->menuAction;
		this->menuAction = 0;
	}
	switch (parm_control_id) {
	case 110: this->menuAction = new ClassMenuAction; break;
	case 111: this->menuAction = new MemoBoxMenuAction; break;
	case 112: this->menuAction = new GeneralizationMenuAction; break;
	case 113: this->menuAction = new RealizationMenuAction; break;
	case 114: this->menuAction = new DependencyMenuAction; break;
	case 115: this->menuAction = new AssociationMenuAction; break;
	case 116: this->menuAction = new DirectedAssociationMenuAction; break;
	case 117: this->menuAction = new AggregationMenuAction; break;
	case 118: this->menuAction = new AggregationsMenuAction; break;
	case 119: this->menuAction = new CompositionMenuAction; break;
	case 120: this->menuAction = new CompositionsMenuAction; break;
	case 121: this->menuAction = new MemoLineMenuAction; break;
	case 123: this->menuAction = new GraphicCtrlUndoMenuAction; break;
	case 107: this->menuAction = new GraphicCtrlCopyMenuAction; break;
	case 108: this->menuAction = new GraphicCtrlPasteMenuAction; break;
	case 109: this->menuAction = new GraphicCtrlCutMenuAction; break;
	case 127: this->menuAction = new AddTemplateMenuAction; break;
	case 128: this->menuAction = new DeleteTemplateMenuAction; break;
	case 129: this->menuAction = new DeleteMenuAction; break;
	case 135: this->menuAction = new AddAttributeMenuAction; break;
	case 131: this->menuAction = new DeleteAttributeMenuAction; break;
	case 130: this->menuAction = new AddMethodMenuAction; break;
	case 132: this->menuAction = new DeleteMethodMenuAction; break;
	case 133: this->menuAction = new AddReceptionMenuAction; break;
	case 134: this->menuAction = new DeleteReceptionMenuAction; break;
	case 136: this->menuAction = new GraphicCtrlRedoMenuAction; break;

	default: break;
	}

	return this->menuAction;
}

ClassDiagramFormMenu& ClassDiagramFormMenu::operator=(const ClassDiagramFormMenu& source) {
	if (this->menu1 != NULL) {
		delete this->menu1;
	}
	if (this->drawMenu != NULL) {
		delete this->drawMenu;
	}
	this->menu1 = source.menu1;
	this->drawMenu = source.drawMenu;

	return *this;
}

ClassDiagramFormMenu::~ClassDiagramFormMenu() {
	if (this->menu1 != NULL) {
		delete this->menu1;
	}
	if (this->menu2 != NULL) {
		delete this->menu2;
	}
	if (this->menu3 != NULL) {
		delete this->menu3;
	}
	if (this->drawMenu != NULL) {
		delete this->drawMenu;
	}
}