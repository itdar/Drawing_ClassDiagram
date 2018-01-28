//Array.h

#ifndef _ARRAY_H
#define _ARRAY_H

typedef signed long int Long;
template <typename T>

class Array {
public:
	Array(Long capacity = 100); // default parameter && default value
	Array(const Array& source); // 복사생성자
	~Array();
	Long Store(Long index, T object);
	Long Insert(Long index, T object);
	Long AppendFromFront(T object);
	Long AppendFromRear(T object);
	Long Delete(Long index);
	Long DeleteFromFront();
	Long DeleteFromRear();
	void Clear();
	Long Modify(Long index, T object);
	Long LinearSearchUnique(void *key, int(*compare)(void*, void*));
	void LinearSearchDuplicate(void *key, Long*(*indexes), Long *count, int(*compare)(void*, void*));
	Long BinarySearchUnique(void *key, int(*compare)(void*, void*));
	void BinarySearchDuplicate(void *key, Long*(*indexes), Long *count, int(*compare)(void*, void*));
	void BubbleSort(int(*compare)(void*, void*));
	void SelectionSort(int(*compare)(void*, void*));
	void InsertionSort(int(*compare)(void*, void*));
	void MergeSort(const Array& one, const Array& other, int(*compare)(void*, void*));
	T& GetAt(Long index);
	Array& operator = (const Array& source); //치환연산자 =
	T& operator [] (Long index); //첨자연산자 []
	T* operator + (Long index); //포인터산술연산자 +
	Long GetCapacity() const;
	Long GetLength() const;
private:
	T(*front);
	Long capacity;
	Long length;
};

template <typename T>
inline Long Array<T>::GetCapacity() const {
	return this->capacity;
}

template <typename T>
inline Long Array<T>::GetLength() const {
	return this->length;
}

template <typename T>
Array<T>::Array(Long capacity) {
	this->front = new T[capacity];
	this->capacity = capacity;
	this->length = 0;
}

template <typename T>   //복사생성자
Array<T>::Array(const Array& source) {
	this->front = new T[source.capacity];
	Long i = 0;
	while (i < source.length) {
		this->front[i] = source.front[i];
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;
}

template <typename T>
Array<T>::~Array() {
	if (this->front != 0) {
		delete[] this->front;
	}
}

template <typename T>
Long Array<T>::Store(Long index, T object) {
	this->front[index] = object;
	this->length++;
	return index;
}

template <typename T>
T& Array<T>::GetAt(Long index) {
	return this->front[index];
}

template <typename T>
Long Array<T>::Insert(Long index, T object) {
	T(*temp);
	temp = new T[this->capacity + 1];
	Long i = 0;
	Long j = 0;
	while (i < index) {
		temp[j] = this->front[i];
		j++;
		i++;
	}
	j++;
	while (i < this->length) {
		temp[j] = this->front[i];
		j++;
		i++;
	}
	if (this->front != 0) {
		delete[] this->front;
		this->front = 0;
	}
	this->front = temp;
	this->capacity++;
	this->front[index] = object;
	this->length++;

	return index;
}

template <typename T>
Long Array<T>::AppendFromFront(T object) {
	Long index = 0;
	T(*temp);
	Long i = 0;
	Long j = 1;

	temp = new T[this->capacity + 1];
	while (i < this->length) {
		temp[j] = this->front[i];
		j++;
		i++;
	}
	if (this->front != 0) {
		delete[] this->front;
	}
	this->front = temp;
	this->capacity++;
	this->front[index] = object;
	this->length++;

	return index;
}

template <typename T>
Long Array<T>::AppendFromRear(T object) {
	Long index;
	T(*temp);
	Long i = 0;
	temp = new T[this->capacity + 1];
	while (i < this->length) {
		temp[i] = this->front[i];
		i++;
	}
	if (this->front != 0) {
		delete[] this->front;
	}
	this->front = temp;
	this->capacity++;
	index = this->capacity - 1;
	this->front[index] = object;
	this->length++;

	return index;
}

template <typename T>
Long Array<T>::Delete(Long index) {
	T(*temp) =0;
	Long i = 0;
	Long j = 0;
	if (this->capacity > 1) {
		temp = new T[this->capacity - 1];
	}
	while (i < index) {
		temp[j] = this->front[i];
		j++;
		i++;
	}
	i++;
	while (i < this->length) {
		temp[j] = this->front[i];
		j++;
		i++;
	}
	if (this->front != 0) {
		delete[] this->front;
		this->front = 0;
	}
	if (this->capacity > 1) {
		this->front = temp;
	}
	this->length--;
	this->capacity--;
	index = -1;

	return index;
}

template <typename T>
Long Array<T>::DeleteFromFront() {
	Long index;
	T(*temp) = 0;
	Long i = 1;
	Long j = 0;
	if (this->capacity > 1) {
		temp = new T[this->capacity - 1];
	}
	while (i < this->length) {
		temp[j] = this->front[i];
		j++;
		i++;
	}
	if (this->front != 0) {
		delete[] this->front;
		this->front = 0;
	}
	if (this->capacity > 1) {
		this->front = temp;
	}
	this->capacity--;
	this->length--;
	index = -1;

	return index;
}

template <typename T>
Long Array<T>::DeleteFromRear() {
	Long index;
	T(*temp) = 0;
	Long i = 0;
	if (this->capacity > 1) {
		temp = new T[this->capacity - 1];
	}
	while (i < this->capacity - 1) {
		temp[i] = this->front[i];
		i++;
	}
	if (this->front != 0) {
		delete[] this->front;
		this->front = 0;
	}
	if (this->capacity > 1) {
		this->front = temp;
	}
	this->capacity--;
	this->length--;
	index = -1;

	return index;
}

template <typename T>
void Array<T>::Clear() {
	if (this->front != 0) {
		delete[] this->front;
		this->front = 0;
	}
	this->capacity = 0;
	this->length = 0;
}

template <typename T>
Long Array<T>::Modify(Long index, T object) {
	this->front[index] = object;

	return index;
}

template <typename T>
Long Array<T>::LinearSearchUnique(void *key, int(*compare)(void*, void*)) {
	Long index = -1;
	Long i = 0;
	while (i < this->length && compare(this->front + i, key) != 0) {
		i++;
	}
	if (i < this->length) {
		index = i;
	}
	return index;
}

template <typename T>
void Array<T>::LinearSearchDuplicate(void *key, Long *(*indexes), Long *count, int(*compare)(void*, void*)) {
	Long i = 0;
	Long j = 0;
	*count = 0;
	*indexes = new Long[this->length];
	while (i < this->length) {
		if (compare(this->front + i, key) == 0) {
			(*indexes)[j] = i;
			(*count)++;
			j++;
		}
		i++;
	}
}

template <typename T>
Long Array<T>::BinarySearchUnique(void *key, int(*compare)(void*, void*)) {
	Long index = -1;
	Long max;
	Long min = 0;
	Long center;
	max = this->length - 1;
	center = (max + min) / 2;
	while (max >= min && compare(this->front + center, key) != 0) {
		if (compare(this->front + center, key) < 0) {
			min = center + 1;
		}
		else {
			max = center - 1;
		}
		center = (max + min) / 2;
	}
	if (max >= min) {
		index = center;
	}
	return index;
}

template <typename T>
void Array<T>::BinarySearchDuplicate(void *key, Long *(*indexes), Long *count, int(*compare)(void*, void*)) {
	Long i = 0;
	Long min = 0;
	*count = 0;
	Long max;
	Long center;
	max = this->length - 1;
	(*indexes) = new Long[this->length];
	center = (max + min) / 2;
	while (max >= min && compare(this->front + center, key) != 0) {
		if (compare(this->front + center, key) < 0) {
			min = center + 1;
		}
		else {
			max = center - 1;
		}
		center = (max + min) / 2;
	}
	min = center - 1;
	while (min >= 0 && compare(this->front + min, key) == 0) {
		min--;
	}
	min++;
	while (min <= max && compare(this->front + min, key) == 0) {
		(*indexes)[i] = min;
		(*count)++;
		i++;
		min++;
	}
}

template <typename T>
void Array<T>::BubbleSort(int(*compare)(void*, void*)) {
	Long i = 0;
	Long j;
	T temp;
	while (i<this->length - 1)
	{
		j = 0;
		while (j < this->length - i - 1) {
			if (compare(this->front + j, this->front + (j + 1)) > 0) {
				temp = this->front[j + 1];
				this->front[j + 1] = this->front[j];
				this->front[j] = temp;
			}
			j++;
		}
		i++;
	}
}

template <typename T>
void Array<T>::SelectionSort(int(*compare)(void*, void*)) {
	Long i = 0;
	Long j;
	T temp;
	while (i < this->length - 1) {
		j = i + 1;
		while (j < this->length) {
			if (compare(this->front + i, this->front + j) > 0) {
				temp = this->front[i];
				this->front[i] = this->front[j];
				this->front[j] = temp;
			}
			j++;
		}
		i++;
	}
}

template <typename T>
void Array<T>::InsertionSort(int(*compare)(void*, void*)) {
	Long i = 1;
	Long j;
	T temp;
	while (i < this->length) {
		temp = this->front[i];
		j = i - 1;
		while (j >= 0 && compare(this->front + j, &temp) > 0) {
			this->front[j + 1] = this->front[j];
			j--;
		}
		this->front[j + 1] = temp;
		i++;
	}
}

template <typename T>
void Array<T>::MergeSort(const Array& one, const Array& other, int(*compare)(void*, void*)) {
	Long i = 0;
	Long j = 0;
	Long k = 0;
	if (this->front != 0) {
		delete[] this->front;
	}
	this->front = new T[one.length + other.length];
	this->capacity = one.length + other.length;
	this->length = 0;
	while (i < one.length && j < other.length) {
		if (compare(one.front + i, other.front + j) < 0) {
			this->front[k] = one.front[i];
			this->length++;
			k++;
			i++;
		}
		else {
			this->front[k] = other.front[j];
			this->length++;
			k++;
			j++;
		}
	}
	while (i < one.length) {
		this->front[k] = one.front[i];
		this->length++;
		k++;
		i++;
	}
	while (j < other.length) {
		this->front[k] = other.front[j];
		this->length++;
		k++;
		j++;
	}
}

template <typename T>
Array<T>& Array<T>::operator = (const Array& source) {

	if (this->front != 0) {
		delete[] this->front;
		front = 0;
	}

	Long i = 0;
	this->front = new T[source.capacity];
	while (i < source.length) {
		this->front[i] = source.front[i];
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;

	return *this;
}

template <typename T>
T* Array<T>::operator + (Long index) { //포인터산술연산자 +
	return this->front + index;
}

template <typename T>
T& Array<T>::operator [] (Long index) { //첨자연산자 []
	return this->front[index];
}



#endif // ! _ARRAY_H
