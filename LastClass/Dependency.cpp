#include "Dependency.h"

Dependency::Dependency(Long capacity):Relation( capacity){

}


Dependency::Dependency(Long x, Long y, Long width, Long height) : Relation(x,y,width,height){

}

Dependency::~Dependency() {

}

Dependency::Dependency(const Dependency& source) :Relation(source){

}

Dependency& Dependency::operator=(const Dependency& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	return *this;
}

void Dependency::Accept(Visitor& visitor, CDC *pDC) {
	visitor.Visit(this, pDC);
}


Figure* Dependency::Clone() const {
	return new Dependency(*this);
}