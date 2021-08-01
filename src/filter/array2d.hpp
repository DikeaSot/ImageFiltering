#include "array2d.h"
#include <vector>
#include <iostream>

using namespace std;

namespace math {

	template <typename T>
	const unsigned int Array2D<T>::getWidth() const {
		return width;
	}
	template <typename T>
	const unsigned int Array2D<T>::getHeight() const {
		return height;
	}
	template <typename T>
	T* Array2D<T>::getRawDataPtr() {
		if (width>0 && height>0) {
			return &buffer[0];
		}
		else {
			return nullptr;
		}
	}
	template <typename T>
	void Array2D<T>::setData(const T* const& data_ptr) {

		if (data_ptr != nullptr) {
			for (int i = 0; i < buffer.size(); i++) {
				buffer[i] = data_ptr[i];
			}
		}else {
			cout << "ERROR"<<endl;
		}

	}

	template <typename T>
	T& Array2D<T>::operator () (unsigned int x, unsigned int y) {
		if(x<width && y<height) {
			return buffer[y * width + x]; 
		}
		else {
			return buffer[0]; //den yparxei alli anafora na epistrafei
		}
		
	}
	template <typename T>
	Array2D<T>::Array2D(unsigned int width, unsigned int height, const T* data_ptr) {
		this->width = width;
		this->height = height;
		buffer.resize(height * width); // allazei to size to kanei w* h
		if (data_ptr != nullptr) setData(data_ptr);
	}

	//kalw tin copy constructor tou buffer mou 
	template <typename T>
	Array2D<T>::Array2D(const Array2D& src) {
		width = src.width;
		height = src.height;
		buffer.resize(width * height);
		for (int i = 0; i < width * height ; i++)
			buffer[i] = src.buffer[i];
	}
	template <typename T>
	Array2D<T>::~Array2D() {
	}

	//operator assignment constructor
	template <typename T>
	Array2D<T>& Array2D<T>::operator = (const Array2D& right) {
		if (this != &right) {
			width = right.width;
			height = right.height;
			buffer.resize(width * height);
			for (int i = 0; i < width * height ; i++)
				buffer[i] = right.buffer[i];
		}
		return *this;
	}
}
