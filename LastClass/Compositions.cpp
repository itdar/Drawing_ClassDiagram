#include "Compositions.h"

Compositions::Compositions(Long capacity):Relation(capacity){

}


Compositions::Compositions(Long x, Long y, Long width, Long height): Relation(x,y,width,height){

}

Compositions::~Compositions() {

}

Compositions::Compositions(const Compositions& source):Relation(source){

}

Compositions& Compositions::operator=(const Compositions& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	return *this;
}

void Compositions::Accept(Visitor& visitor, CDC *pDC) {
	visitor.Visit(this, pDC);
}


Figure* Compositions::Clone() const {
	return new Compositions(*this);
}
