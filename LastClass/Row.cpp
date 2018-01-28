//Row.cpp

#include "Row.h"
#include "Character.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
#include "Visitor.h"

Row::Row(Long capacity) : TextComposite(capacity) {
	this->capacity = capacity;
	this->length = 0;
}

Row::Row(const Row& source) {
	this->textComponents = source.textComponents;
	this->capacity = source.capacity;
	this->length = source.length;
	Long i = 0;
	while (i < source.length) {
		this->textComponents.Modify(i, (const_cast<Row&>(source)).textComponents[i]->Clone());
		i++;
	}
}

Row::~Row() {
}

Long Row::Add(TextComponent *textComponent) {
	Long index;
	if (this->length < this->capacity) {
		index = this->textComponents.Store(this->length, textComponent);
	}
	else {
		index = this->textComponents.AppendFromRear(textComponent);
		this->capacity++;
	}
	this->length++;
	return index;
}

Long Row::Add(Character *character) {
	Long index;
	if (this->length < this->capacity) {
		index = this->textComponents.Store(this->length, character->Clone());
	}
	else {
		index = this->textComponents.AppendFromRear(character->Clone());
		this->capacity++;
	}
	this->length++;
	return index;
}

Long Row::Modify(Long index, TextComponent *textComponent) {
	return this->textComponents.Modify(index, textComponent);
}

Long Row::Remove(Long index) {
	index = this->textComponents.Delete(index);
	this->length--;
	this->capacity--;

	return index;
}

Long Row::Insert(Long index, TextComponent *textComponent) {
	this->length++;
	this->capacity++;
	return this->textComponents.Insert(index, textComponent);
}

string Row::PrintRowString() {
	char tempChar[512] = { 0, };
	Long i = 0;

	SmartPointer<TextComponent*> iterator = this->CreateIterator();
	for (iterator->First(); !iterator->IsDone(); iterator->Next()) {
		if (dynamic_cast<SingleByteCharacter*>(iterator->Current())) {
			tempChar[i] = static_cast<SingleByteCharacter*>(iterator->Current())->GetCharacter();
		}
		else if (dynamic_cast<DoubleByteCharacter*>(iterator->Current())) {
			tempChar[i] = static_cast<DoubleByteCharacter*>(iterator->Current())->GetCharacters()[0];
			i++;
			tempChar[i] = static_cast<DoubleByteCharacter*>(iterator->Current())->GetCharacters()[1];
		}
		i++;
	}
	string tempString(tempChar, i);

	return tempString;
}

Long Row::GetRowWidth(CDC* pDC, Long to, Long from) {
	CString str;
	Long x = 0;
	Long column = 0;
	Long tabWidth = 0;
	Long i = from;
	Long j = 0;
	while (i < to) {
		str = this->GetAt(i)->MakeCString();
		if (str.GetAt(0) & 0x80) { // 2¹ÙÀÌÆ®¹®ÀÚ¸é 2Ä­
			column += 2;
		}
		else if (str == "\t") { // ÅÇ¹®ÀÚ¸é ÀÌÀü¹®ÀÚÀÇ Ä­À» ¼À
			tabWidth = (column + 8) / 8 * 8 - column;
			column += tabWidth;
			j = 0;
			str = "";
			while (j < tabWidth) { //±¸ÇÑ Ä­¸¸Å­ ÅÇ¹®ÀÚÀÇ Å©±â¸¦ Á¤ÇÔ
				str += " ";
				j++;
			}
		}
		else { // 1¹ÙÀÌÆ®¹®ÀÚ¸é 1Ä­
			column += 1;
		}
		x += pDC->GetTextExtent(str).cx;
		i++;
	}
	return x;
}

Character* Row::GetAt(Long index) {
	return static_cast<Character*>(this->textComponents[index]);
}

TextComponent* Row::Clone() const {
	return new Row(*this);
}

Row& Row::operator = (const Row& source) {
	this->capacity = source.capacity;
	this->length = source.length;
	this->textComponents = source.textComponents;
	Long i = 0;
	while (i < source.length) {
		this->textComponents.Modify(i, (const_cast<Row&>(source)).textComponents.GetAt(i)->Clone());
		i++;
	}
	return *this;
}

Character* Row::operator [] (Long index) {
	return static_cast<Character*>(this->textComponents[index]);
}