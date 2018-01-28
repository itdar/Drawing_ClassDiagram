//HistoryGraphic.h

#ifndef _HISTORYGRAPHIC_H
#define _HISTORYGRAPHIC_H

#include "Array.h"

typedef signed long int Long;

class Diagram;

class HistoryGraphic {
public:
	static HistoryGraphic* Instance();

	HistoryGraphic();
	HistoryGraphic(const HistoryGraphic& source);
	~HistoryGraphic();

	void PushUndo(Diagram *diagram, Long zoomRate);
	void PopUndoGraphic(Diagram*(*diagram), Long *zoomRate);

	void PushRedo(Diagram *diagram, Long zoomRate);
	void PopRedoGraphic(Diagram*(*diagram), Long *zoomRate);

public:
	Array<Diagram*>*undoGraphicArray;
	Array<Diagram*>*redoGraphicArray;
	Array<Long>*undoGraphicZoomRateArray;
	Array<Long>*redoGraphicZoomRateArray;

	static HistoryGraphic* instance;
};


#endif // _HISTORYGRAPHIC_H
