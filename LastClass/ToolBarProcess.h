//ToolBarProcess.h

#ifndef _TOOLBARPROCESS_H
#define _TOOLBARPROCESS_H

#include <afxwin.h>
typedef signed long int  Long;
class LastClass;
class ClassDiagramForm;
class ToolBarProcess{
public:
	ToolBarProcess();
	ToolBarProcess(const ToolBarProcess& source);
	~ToolBarProcess();
	void OnNewFileClicked(LastClass *lastClass);
	void OnOpenClicked(LastClass *lastClass);
	void OnSaveFileClicked(LastClass *lastClass);
	void OnRedoFileClicked(LastClass *lastClass);
	void OnUndoFileClicked(LastClass *lastClass);
	void OnCutFileClicked(LastClass *lastClass);
	void OnCopyFileClicked(LastClass *lastClass);
	void OnPasteFileClicked(LastClass *lastClass);
	void OnFinishFileClicked(LastClass *lastClass);
	void OnPrintFileClicked(LastClass *lastClass);
	void OnPrintPreFileClicked(LastClass *lastClass);
	void OnSupportFileClicked(LastClass *lastClass);
	void OnAboutFileClicked(LastClass *lastClass);
	void OnClassClicked(LastClass *lastClass);
	void OnMemoBoxClicked(LastClass *lastClass);
	void OnGeneralizationClicked(LastClass *lastClass);
	void OnRelizationClicked(LastClass *lastClass);
	void OnDependencyClicked(LastClass *lastClass);
	void OnAssociationClicked(LastClass *lastClass);
	void OnDirectedAssociationClicked(LastClass *lastClass);
	void OnAggregationClicked(LastClass *lastClass);
	void OnAggregationsClicked(LastClass *lastClass);
	void OnCompositionClicked(LastClass *lastClass);
	void OnCompositionsClicked(LastClass *lastClass);
	void OnMemoLineClicked(LastClass *lastClass);
	void OnZoomInClicked(LastClass *lastClass);
	void OnZoomOutClicked(LastClass *lastClass);
};

#endif // _ToolBar_H

