#include "Composition.h"

Composition::Composition(Long capacity):Relation(capacity){

}


Composition::Composition(Long x, Long y, Long width, Long height): Relation(x,y,width,height){

}

Composition::~Composition() {

}

Composition::Composition(const Composition& source):Relation(source){

}

Composition& Composition::operator=(const Composition& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	return *this;
}

void Composition::Accept(Visitor& visitor, CDC *pDC) {
	visitor.Visit(this, pDC);
}


Figure* Composition::Clone() const {
	return new Composition(*this);
}
