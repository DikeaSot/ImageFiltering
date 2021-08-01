#include <iostream>
#include <string>
#include "image.h"
#include "Filter.h"

using namespace std;
using namespace image;


int main(int argc,char*argv[]) {

	//p.x filter -f gamma 2.0 image.ppm
	if (argc < 5) {
		cout << "we don't have all the necessary things!!"<<endl;
	}
	else {
		Image imag;
	    string arxeio = argv[argc - 1];
		
		imag.load(arxeio, "ppm");
		Vec3 <float> a;
		Vec3 <float> c;
		float g;
		for (int i = 0; i < argc; i++) {
			//string s = argv[i]; idio me katw
			if (string(argv[i]) == "-f") {
				if (string(argv[i + 1]) == "linear"){
					a.r = atof(argv[i + 2]);
					a.g = atof(argv[i + 3]);
					a.b = atof(argv[i + 4]);
					c.r = atof(argv[i + 5]);
					c.g = atof(argv[i + 6]);
					c.b = atof(argv[i + 7]);
					FilterLinear filters(a, c);
					imag = filters << imag;
				}
				else if (string(argv[i + 1]) == "gamma") {
					g = atof(argv[i + 2]);
					FilterGamma filters(g);

					
					imag = filters << imag;
					
				}
			}
		}
		arxeio.erase(arxeio.length() - 4);
		bool saved = imag.save(arxeio + "_filtered.ppm", "ppm");
		if (saved) {
			cout << "All good image saved"<<endl;
		}
		else {
			cout << "Something goes wrong"<<endl;
		}

		
	}

}