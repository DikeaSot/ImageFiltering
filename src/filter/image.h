#pragma once
#include "imageio.h"
#include "array2d.h"
#include "vec3.h"
#include "ppm.h"

using namespace math;
namespace image {
	class Image : public  ImageIO, public Array2D<Vec3<float>> {
	public:
		bool load(const std::string& filename, const std::string& format) {

			int w, h;
			int j = 2;

			//i for ginetai gia na paroume to ppm 
			for (int i = filename.length() - 1; i > filename.length() - 4; i--) {
				
				if (filename[i] != format[j]) {
					return false;
				}
				j--;
			}
			float* pic = ReadPPM(filename.c_str(), &w, &h);
			if (pic != nullptr) {
				width = w;
				height = h;
				//kanoume resize gia na valoume se ena keli to rgb 
				buffer.resize(w * h);
				for (int i = 0; i < w * h * 3; i+=3) {
					buffer[i/3].r = pic[i];
					buffer[i/3].g = pic[i+1];
					buffer[i/3].b = pic[i+2];
				}
				delete pic;
				return true;
			}
			else {
				cout << "Wrong format"<<endl;
				return false;
			}
		}

		 bool save(const std::string& filename, const std::string& format) {
			 int j = 2;


			 for (int i = filename.length() - 1; i > filename.length() - 4; i--) {
				 if (filename[i] != format[j]) {
					 return false;
				 }
				 j--;
			 }

			 float* pic = new float[width * height * 3];
			 for (int i = 0; i < width * height * 3; i+=3) {
				 pic[i] = buffer[i/3].r;
				 pic[i + 1] = buffer[i/3].g;
				 pic[i + 2] = buffer[i/3].b;
			 }

			 if (WritePPM(pic, width, height, filename.c_str())) {
				 cout << "Image Saved"<<endl;
				 delete [] pic;
				 return true;
			 }
			 else {
				 cout << "Something went wrong while saving the image"<<endl;
				 delete [] pic;
				 return false;
			 }
		 }
	};
}