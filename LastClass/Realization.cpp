#include "Realization.h"

Realization::Realization(Long capacity) :Relation(capacity){

}


Realization::Realization(Long x, Long y, Long width, Long height): Relation(x,y,width,height){
	
}

Realization::~Realization() {

}

Realization::Realization(const Realization& source):Relation(source){

}

Realization& Realization::operator=(const Realization& source){
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	return *this;
}

void Realization::Accept(Visitor& visitor, CDC *pDC) {
	visitor.Visit(this, pDC);
}


Figure* Realization::Clone() const {
	return new Realization(*this);
}