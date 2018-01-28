#include "MemoLine.h"

MemoLine::MemoLine(Long capacity):Relation( capacity){

}


MemoLine::MemoLine(Long x, Long y, Long width, Long height) : Relation(x,y,width,height){

}

MemoLine::~MemoLine() {

}

MemoLine::MemoLine(const MemoLine& source):Relation(source){

}

MemoLine& MemoLine::operator=(const MemoLine& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	return *this;
}

void MemoLine::Accept(Visitor& visitor, CDC *pDC) {
	visitor.Visit(this, pDC);
}


Figure* MemoLine::Clone() const {
	return new MemoLine(*this);
}