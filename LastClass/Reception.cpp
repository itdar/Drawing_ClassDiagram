//Reception.cpp

#include "Reception.h"
#include <iostream>
using namespace std;

Reception::Reception() : Figure() {
}

Reception::~Reception() {
}

Reception::Reception(Long x, Long y, Long width, Long height, string content) : Figure(x, y, width, height, content) {
}

Reception::Reception(Long x, Long y, Long width, Long height, Long minimumWidth, Long minimumHeight, string content)
	: Figure(x, y, width, height, minimumWidth, minimumHeight, content) {
}

Reception::Reception(const Reception& source) : Figure(source) {
}

Reception& Reception::operator = (const Reception& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	this->content = source.content;

	return *this;
}

Figure* Reception::Clone() const {
	return new Reception(*this);
}

void Reception::Accept(Visitor& visitor, CDC *pDC) {
	visitor.Visit(this, pDC);
}