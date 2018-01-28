#ifndef _CLASSDIAGRAMFORMMENU_H	
#define _CLASSDIAGRAMFORMMENU_H

#include <afxwin.h>

using namespace std;
class ClassDiagramForm;
class MenuAction;
class ClassDiagramFormMenu {
public:
	ClassDiagramFormMenu(ClassDiagramForm *classDiagramForm);
	~ClassDiagramFormMenu();
	ClassDiagramFormMenu(const ClassDiagramFormMenu& source);
	MenuAction* MenuSelected(UINT parm_control_id);
	ClassDiagramFormMenu& operator= (const ClassDiagramFormMenu& source);
public:
	CMenu *menu1;  // 선택된게 없을때
private:
	CMenu *drawMenu; 
public:
	CMenu *menu2;	//선택된게 1개
public:
	CMenu *menu3;  //선택된게 2개
public:
	MenuAction *menuAction;
	ClassDiagramForm *classDiagramForm;
};
#endif // !_CLASSDIAGRAMFORMMENU_H
