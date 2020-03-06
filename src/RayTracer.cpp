
#include <cmath>
#include <iostream>
#include <algorithm>

#include "Tracer.h"
#include "Bitmap.h"
#include "Ray.h"

int main(int argc, const char* argv[]) {
	const float width = 800.f;
	const float height = 600.f;

	Bitmap bmp;
	bmp.SetHeader(width, height);
	Tracer tracer;

	int padd = 5;
	float marg = 1.f / padd; 
	float limit = padd / 2.f; 

	Ray ray;
	ray.origin = {0.f, 0.f, 0.f};

	color col;
	float aspectRatio = float(width) / float(height);

	float rx = 0, ry = 0;
	
	for (float j = 0.f; j < height; j++) {
		for (float i = 0.f; i < width; i++) {

			col = {0.f, 0.f, 0.f};

			for (int l = 0; l < padd; l++) {
				for (int k = 0; k < padd; k++) {
					/*
					float LO = -marg / 2.f;
					float HI = marg / 2.f;

					srand(static_cast<unsigned>(time(0)));
					float rx = LO + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (HI - LO)));
					srand(static_cast<unsigned>(time(0)));
					float ry = LO + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (HI - LO)));
					*/

					float cx = i + (marg * (k - limit)) + rx;
					float cy = j + (marg * (l - limit)) + ry;

					// calcul des coordonnees monde des pixels
					float x = aspectRatio * 2.f * (float(cx - width / 2) + 0.5f) / width;
					float y = -2.f * (float(cy - height / 2) + 0.5f) / height;

					ray.direction = {x, y, 1.f};
					ray.direction.normalize();

					col = col + tracer.Trace(ray);
				}
			}

			col = col / (padd * padd);

			col.r = std::min(1.0f, col.r);
			col.g = std::min(1.0f, col.g);
			col.b = std::min(1.0f, col.b);

			int r = int(powf(col.r, 1.f / 2.2f) * 255.99f);
			int g = int(powf(col.g, 1.f / 2.2f) * 255.99f);
			int b = int(powf(col.b, 1.f / 2.2f) * 255.99f);

			bmp.OutputColor(r, g, b);
		}
	}

	return 0;
}

/*
	float jitterMatrix[4 * 2] = {
		-1.0f/4.0f,  3.0f/4.0f,
		3.0f/4.0f,  1.0f/3.0f,
		-3.0f/4.0f, -1.0f/4.0f,
		1.0f/4.0f, -3.0f/4.0f,
	};



			for (int sample = 0; sample < 4; ++sample) {
				ray.origin = {0.f, 0.f, 0.f};

				float x = aspectRatio * 2.f * (float((i + jitterMatrix[2 * sample]) - width / 2) + 0.5f) / width;
				float y = -2.f * (float((j + jitterMatrix[2 * sample + 1]) - height / 2) + 0.5f) / height;

				ray.direction = {x, y, 1.f};
				ray.direction.normalize();

				col = col + tracer.Trace(ray);
			}

			// Get the average.
			col = col / 4.0f;
*/