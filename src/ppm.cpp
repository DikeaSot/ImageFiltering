#include <string>
#include <fstream>
#include <iostream>

#include "ppm.h"

using namespace std;
namespace image 
{
	
	float* ReadPPM(const char* filename, int* w, int* h) {
		//reading file
		ifstream arxeio = ifstream(filename, ios_base::in | ios_base::binary);
		string epik;
		int width;
		int height;
		int color;
		unsigned char rgb;

		
		if (arxeio) {
			arxeio >> epik >> width >> height >> color;
			if (epik == "P6" && width > 0 && height > 0 && color == 255) {
				
				*w = width;
				*h = height;

				arxeio.get(); //metakinoume ton kersora stin arxi tou binary keimenou

				float* pic = new float[width * height * 3];//* 3 gt exoume rgb 

				
				for (int i = 0; i < width * height * 3; i++) {
					arxeio.read((char*) &rgb, sizeof(unsigned char));
					pic[i] = rgb / 255.0f; //gt theloume to pic na pairnei times apo 0-1
				}

				arxeio.close();
				cout << "File closed!"<<endl;
				return pic;                
			}
			else {
				arxeio.close();
				cout << "Heading error!!"<<endl;
				return nullptr;
			}
		}else {
			cout << "Error opening file!!"<<endl;
			return nullptr;
		}
		
	}

	bool WritePPM(const float* data, int w, int h, const char* filename) {
		if (data == nullptr) return false;
		ofstream arxeio = ofstream(filename, ios_base::out | ios_base::binary);
		if (arxeio) {
			unsigned char rgb;
			arxeio << "P6\n" << w << "\n" << h << "\n255\n"; //write heading of file

			for (int i = 0; i < w * h * 3; i++) {
				rgb = data[i] * 255;
				arxeio.write((char*) &rgb, sizeof(unsigned char));
			}

			arxeio.close();
			cout << "File successfully written!"<<endl;
			return true;
		}
		else {
			cout << "Error Writing File!"<<endl;
			return false;

		}
		


	}

}