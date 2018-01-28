
//SmartPointer.h

#ifndef _SMARTPOINTER_H
#define _SMARTPOINTER_H

#include "Iterator.h"

template<typename T>
class SmartPointer {
public:
	SmartPointer(Iterator<T>* index);
	~SmartPointer();
	Iterator<T>* operator->();
	Iterator<T>& operator*();
private:
	SmartPointer(const SmartPointer&);
	//SmartPointer& operator = (const SmartPointer&);
private:
	Iterator<T>* index;
};

template<typename T>
SmartPointer<T>::SmartPointer(Iterator<T>* index) :index(index) {
}
template<typename T>
SmartPointer<T>::~SmartPointer() {
	delete index;
}
template<typename T>
Iterator<T>* SmartPointer<T>::operator -> (){
	return index;
}
template<typename T>
Iterator<T>& SmartPointer<T>::operator * () {
	return *index;
}

#endif // !_SMARTPOINTER_H