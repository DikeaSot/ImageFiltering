
#pragma once
#include "image.h"
using namespace image;
using namespace math;

class Filter {
public:
	virtual Image operator << (const Image& image) = 0;
};


class FilterLinear :public Filter {

	Vec3<float> a, c;
public:

	//constructor
	FilterLinear(Vec3<float> a, Vec3<float> c) {
		this->a = a;
		this->c = c;
	}
	//copyConstructor

	FilterLinear(const FilterLinear& right) {
		a = right.a;
		c = right.c;
	}

	Image operator << (const Image& image) {

		Image copy = image;

		Vec3<float>* pic = copy.getRawDataPtr();
		for (int i = 0; i < copy.getWidth() * copy.getHeight(); i++) {
			pic[i] = a * pic[i] + c;
			
			//red
			if (pic[i].r > 1) {
				pic[i].r = 1;
			}
			else if(pic[i].r<0){
				pic[i].r = 0;
			}

			//green
			if (pic[i].g > 1) {
				pic[i].g = 1;
			}
			else if (pic[i].g < 0) {
				pic[i].g = 0;
			}

			//blue
			if (pic[i].b > 1) {
				pic[i].b = 1;
			}
			else if (pic[i].b < 0) {
				pic[i].b = 0;
			}
		}
		return copy;
	}
};

class FilterGamma :public Filter {
	float g;

public:
	// constructor
	FilterGamma(float g) {
		this->g = g;
	}
	//copy
	FilterGamma(const FilterGamma& right) {
		g = right.g;
	}

	Image operator << (const Image& image) {


		Image copy = image;

		Vec3<float>* pic = copy.getRawDataPtr();
		for (int i = 0; i < copy.getWidth() * copy.getHeight(); i++) {
			pic[i].r =  pow(pic[i].r ,g);
			pic[i].g = pow(pic[i].g, g);
			pic[i].b = pow(pic[i].b, g);
		}

		return copy;
	}
};