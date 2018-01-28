#ifndef _SCROLLMOVINGOBJECT_H
#define _SCROLLMOVINGOBJECT_H

typedef signed long int Long;
class Diagram;
class ScrollMovingObject {
public:
	ScrollMovingObject();
	ScrollMovingObject(const ScrollMovingObject& source);
	ScrollMovingObject& operator = (const ScrollMovingObject& source);
	~ScrollMovingObject();
	void MovingObject(Diagram* diagram, Long distanceX = 0, Long distanceY = 0);
	bool FindHorizontal(Diagram* diagram, Long x);
	Long GetHorizontalMax(Diagram* diagram);
	bool FindVertical(Diagram* diagram, Long y);
	Long GetVerticalMax(Diagram* diagram);
};
#endif // !_SCROLLMOVINGOBJECT_H