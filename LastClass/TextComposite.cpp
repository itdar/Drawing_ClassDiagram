//TextComposite.cpp

#include "TextComposite.h"

TextComposite::TextComposite(Long capacity) : textComponents(capacity) {
	this->capacity = capacity;
	this->length = 0;
}
TextComposite::TextComposite(const TextComposite& source) : textComponents(source.textComponents) {
	Long i = 0;
	while (i < source.length) {
		this->textComponents.Modify(i, (const_cast<TextComposite&>(source)).textComponents[i]->Clone());
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;
}
TextComposite::~TextComposite() {
	Long i = 0;
	while (i < this->length) {
		delete this->textComponents[i];
		i++;
	}
}
TextComposite& TextComposite::operator = (const TextComposite& source) {
	Long i = 0;
	this->textComponents = source.textComponents;
	while (i < source.length) {
		this->textComponents.Modify(i, (const_cast<TextComposite&>(source)).textComponents[i]->Clone());
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;

	return *this;
}
ArrayIterator<TextComponent*>* TextComposite::CreateIterator() const {
	return new ArrayIterator<TextComponent*>(&this->textComponents);
}