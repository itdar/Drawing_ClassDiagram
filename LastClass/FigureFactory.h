//FigureFactory.h
#ifndef _FIGUREFACTORY_H
#define _FIGUREFACTORY_H

#include <string>

typedef signed long int Long;

using namespace std;

class TextComponent;
class Figure;
class FigureFactory {
public:
	FigureFactory();
	~FigureFactory();
	Figure* Create(Long x, Long y, Long width, Long height, Long minimumWidth, Long minimumHeight, Long type);
};

#endif // !_FIGUREFACTORY_H

