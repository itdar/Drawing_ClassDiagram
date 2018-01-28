//Method.cpp

#include "Method.h"

Method::Method() : Figure() {
}

Method::~Method() {
}

Method::Method(Long x, Long y, Long width, Long height, string content) : Figure(x, y, width, height, content) {
}

Method::Method(Long x, Long y, Long width, Long height, Long minimumWidth, Long minimumHeight, string content)
	: Figure(x, y, width, height, minimumWidth, minimumHeight, content) {
}

Method::Method(const Method& source) : Figure(source) {
}

Method& Method::operator = (const Method& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	this->content = source.content;

	return *this;
}

Figure* Method::Clone() const {
	return new Method(*this);
}

void Method::Accept(Visitor& visitor, CDC *pDC) {
	visitor.Visit(this, pDC);
}