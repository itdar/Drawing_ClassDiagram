//TextComposite.h

#ifndef _TEXTCOMPOSITE_H
#define _TEXTCOMPOSITE_H

#include "TextComponent.h"
#include "Array.h"
#include "ArrayIterator.h"
#include "SmartPointer.h"

typedef signed long int Long;

class Character;
class TextComposite : public TextComponent {
public:
	TextComposite(Long capacity = 256);
	TextComposite(const TextComposite& source);
	virtual ~TextComposite() = 0;

	virtual Long Add(TextComponent *textComponent) = 0;
	virtual Long Remove(Long index) = 0;
	virtual Long Insert(Long index, TextComponent *textComponent) = 0;
	//virtual TextComponent* GetAt(Long index);

	virtual TextComponent* Clone() const = 0;
	ArrayIterator<TextComponent*>* CreateIterator() const;

	TextComposite& operator = (const TextComposite& source);
	Long GetCapacity() const;
	Long GetLength() const;
protected:
	Array<TextComponent*> textComponents;
	Long capacity;
	Long length;
};

inline Long TextComposite::GetCapacity() const {
	return this->capacity;
}
inline Long TextComposite::GetLength() const {
	return this->length;
}

#endif // TEXTCOMPOSITE_H