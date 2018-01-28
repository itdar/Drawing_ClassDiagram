//Attribute.cpp

#include "Attribute.h"

Attribute::Attribute() : Figure() {
}
Attribute::~Attribute() {
}
Attribute::Attribute(Long x, Long y, Long width, Long height, string content) : Figure(x, y, width, height, content) {
}
Attribute::Attribute(Long x, Long y, Long width, Long height, Long minimumWidth, Long minimumHeight, string content)
	: Figure(x, y, width, height, minimumWidth, minimumHeight, content) {
}
Attribute::Attribute(const Attribute& source) : Figure(source) {
}
Attribute& Attribute::operator = (const Attribute& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	this->content = source.content;

	return *this;
}
Figure* Attribute::Clone() const {
	return new Attribute(*this);
}
void Attribute::Accept(Visitor& visitor, CDC *pDC) {
   visitor.Visit(this, pDC);
}