#include "Generalization.h"

Generalization::Generalization(Long capacity):Relation(capacity){
}


Generalization::Generalization(Long x, Long y, Long width, Long height) : Relation(x,y,width,height){

}

Generalization::~Generalization() {

}

Generalization::Generalization(const Generalization& source):Relation(source){
	
}

Generalization& Generalization::operator=(const Generalization& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	return *this;
}

void Generalization::Accept(Visitor& visitor, CDC *pDC) {
	visitor.Visit(this, pDC);
}

Figure* Generalization::Clone() const {
	return new Generalization(*this);
}
