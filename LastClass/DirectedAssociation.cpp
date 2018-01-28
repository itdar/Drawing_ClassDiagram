//DirectedAssociation.cpp
// 직접연관

#include "DirectedAssociation.h"

DirectedAssociation::DirectedAssociation(Long capacity) :Relation( capacity){

}

DirectedAssociation::DirectedAssociation(Long x, Long y, Long width, Long height): Relation(x,y,width,height){

}

DirectedAssociation::~DirectedAssociation() {

}

DirectedAssociation::DirectedAssociation(const DirectedAssociation& source):Relation(source){

}

DirectedAssociation& DirectedAssociation::operator=(const DirectedAssociation& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	return *this;
}

void DirectedAssociation::Accept(Visitor& visitor, CDC *pDC) {
	visitor.Visit(this, pDC);
}

Figure* DirectedAssociation::Clone() const {
	return new DirectedAssociation(*this);
}