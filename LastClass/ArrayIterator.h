
//ArrayIterator.h

#ifndef _ARRAYITERATOR_H
#define _ARRAYITERATOR_H

#include "Array.h"
#include "Iterator.h"

typedef signed long int Long;

template<typename T>
class ArrayIterator : public Iterator<T> {
public:
	ArrayIterator(const Array<T>* array);
	virtual void First();
	virtual void Previous();
	virtual void Next();
	virtual bool IsDone() const;
	virtual T Current() const;
private:
	const Array<T>* array;
	Long current;
};

template<typename T>
ArrayIterator<T>::ArrayIterator(const Array<T>* array) {
	this->array = array;
	this->current = 0;
}

template<typename T>
void ArrayIterator<T>::First() {
	this->current = 0;
}

template<typename T>
void ArrayIterator<T>::Previous() {
	this->current--;
}

template<typename T>
void ArrayIterator<T>::Next() {
	this->current++;
}

template<typename T>
bool ArrayIterator<T>::IsDone() const {
	bool ret = true;
	if (this->current < this->array->GetLength()) {
		ret = false;
	}
	return ret;
}

template<typename T>
T ArrayIterator<T>::Current() const {
	return (const_cast<Array<T>*>(this->array))->GetAt(this->current);
}

#endif // _ARRAYITERATOR_H