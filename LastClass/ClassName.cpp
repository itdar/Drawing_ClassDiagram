//ClassName.cpp

#include "ClassName.h"

ClassName::ClassName() : Figure() {
}

ClassName::~ClassName() {
}

ClassName::ClassName(Long x, Long y, Long width, Long height, string content) : Figure(x, y, width, height, content) {
}

ClassName::ClassName(Long x, Long y, Long width, Long height, Long minimumWidth, Long minimumHeight, string content) 
	: Figure(x, y, width, height, minimumWidth, minimumHeight, content) {
}

ClassName::ClassName(const ClassName& source) : Figure(source) {
}

ClassName& ClassName::operator = (const ClassName& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	this->content = source.content;

	return *this;
}

Figure* ClassName::Clone() const {
	return new ClassName(*this);
}

void ClassName::Accept(Visitor& visitor, CDC *pDC) {
	visitor.Visit(this, pDC);
}