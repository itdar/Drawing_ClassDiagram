//StatusBar.h

#ifndef _STATUSBAR_H
#define _STATUSBAR_H

#include <afxext.h>
#include <afxwin.h>

typedef signed long int Long;

class LastClass;
class ClassDiagramForm;
class StatusBar {
public:
	StatusBar();
	StatusBar(const StatusBar& source);
	~StatusBar();
public:

public:
	HWND MakeStatusBar(LastClass *lastClass, HWND hwndParent, int idStatus, HINSTANCE hinst, int cParts);
	void ChangeStatusBarSize(RECT *rect);
	void DestroyStatus();
	HWND hStatus;
private:
};

#endif // _STATUSBAR_H
