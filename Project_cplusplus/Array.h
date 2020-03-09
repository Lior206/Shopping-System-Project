#ifndef _ARRAY_H
#define _ARRAY_H

#include "validate.h"

/*
T should have:
- clone()
*/

template<class T>
class Array
{
public:
	Array();
	Array(int pSize);
	Array(const Array& other);
	~Array();

	int getLsize() const;
	int getPsize() const;
	T** getArr() const;
	void operator+=(const T* other);
	T* operator[](int index) const;
protected:
	int pSize, lSize;
	T** arr;
};

template<class T>
Array<T>::Array() : pSize(1), lSize(0)
{
	arr = new T*[pSize];
	Validate::dynamicAlloc(arr);
}
template<class T>
Array<T>::Array(int pSize) : pSize(pSize), lSize(0)
{
	arr = new T*[pSize];
	Validate::dynamicAlloc(arr);
}

template<class T>
Array<T>::Array(const Array& other)
{
	pSize = other.pSize;
	lSize = other.lSize;
	arr = new T*[pSize];
	for (int i = 0; i < lSize;i++)
		arr[i] = other.arr[i]->clone();
}

template<class T>
Array<T>::~Array()
{
	for (int i = 0;i < this->lSize;i++)
		delete arr[i];
	delete[] arr;
}

template<class T>
int Array<T>::getLsize() const
{
	return this->lSize;
}

template<class T>
int Array<T>::getPsize() const
{
	return pSize;
}

template<class T>
T** Array<T>::getArr() const
{
	return arr;
}

template<class T>
void Array<T>::operator+=(const T* other)
{
	lSize++;
	if (lSize > pSize)
	{
		pSize *= 2;
		T** newArr = new T*[pSize];
		Validate::dynamicAlloc(newArr);
		for (int i = 0; i < lSize - 1; i++)
			newArr[i] = arr[i];
		newArr[lSize - 1] = other->clone();
		
		delete []arr;
		arr = newArr;
	}
	else
		arr[lSize - 1] = other->clone();
}

template<class T>
T* Array<T>::operator[](int index) const
{
	return arr[index];
}
#endif // !_ARRAY_H

