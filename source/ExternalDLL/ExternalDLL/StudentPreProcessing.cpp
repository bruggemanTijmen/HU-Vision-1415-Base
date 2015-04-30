#include "StudentPreProcessing.h"
#include "IntensityImageStudent.h"
#include "ImageIO.h"
#include "iostream"
#include <math.h>
IntensityImage * StudentPreProcessing::stepToIntensityImage(const RGBImage &image) const {
	IntensityImageStudent* IntensityImage = new IntensityImageStudent{ image.getWidth(), image.getHeight() };

	for (int i = 0; i < (image.getWidth() * image.getHeight()); i++) {
		RGB pixel = image.getPixel(i);

		const int average = (pixel.b + pixel.g + pixel.r) / 3;
		Intensity it(average);
		IntensityImage->setPixel(i, it);
	}
	return IntensityImage;
}

IntensityImage * StudentPreProcessing::stepScaleImage(const IntensityImage &image) const {
	return nullptr;
}
IntensityImage * add_mask(const IntensityImage &image, std::vector<float> mask);
IntensityImage * StudentPreProcessing::stepEdgeDetection(const IntensityImage &image) const {

	std::vector<float>mask = { 0, 0, -1, -2, -1, 0, 0, //////////la placien
								0, -2, -3, -4, -3, -2, 0,
								-1, -3, 1, 9, 1, -3, -1,
								-2, -4, 9, 22, 9, -4, -2,
								-1, -3, 1, 9, 1, -3, -1,
								0, -2, -3, -4, -3, -2, 0,
								0, 0, -1, -2, -1, 0, 0 };

	std::vector<float> mask3 = { 0, 0, 0, 0, 0,
								0, -1, 6, -1, 0,
								0, -0.5, -1, -0.5, 0,
								0, -0.5, -1, -0.5, 0,
								0, -0, 0, 0, 0 };

	std::vector<float> mask5 = { 0, 1, 0,
								1, -4, 1,
								-0, 1, 0, };

	std::vector<float> gaussian_mask = { 1, 2, 3, 2, 1,
										2, 7, 11, 7, 2,
										3, 11, 17, 11, 3,
										2, 7, 11, 7, 2,
										1, 2, 3, 2, 1 };

	std::vector<float> gaussian_mask2 = { 2, 4, 5, 4, 2,
										4, 9, 12, 9, 4,
										5, 12, 15, 12, 5,
										4, 9, 12, 9, 4,
										2, 4, 5, 4, 2 };

	
	std::vector<float> high_pass_mask = { -1, -1, -1,
										-1, 8, -1,
										- 1, -1, -1 };

	IntensityImage * blur = add_mask(image, gaussian_mask2);
	ImageIO::saveIntensityImage(*blur, ImageIO::getDebugFileName("blur.png"));
	IntensityImage * high_pass = add_mask(*blur, high_pass_mask);
	IntensityImageStudent* sharp = new IntensityImageStudent{ image.getWidth(), image.getHeight() };
	for (int i = 0; i < blur->getHeight()*blur->getWidth();i++){ ///////////////////////// HIER ZIT DE BUGG
		int pixel = blur->getPixel(i) + high_pass->getPixel(i);
		if (pixel > 255){ pixel = 255; }
		sharp->setPixel(i, Intensity(pixel));
	}
	ImageIO::saveIntensityImage(*sharp, ImageIO::getDebugFileName("sharp.png"));
	IntensityImage* Done = add_mask(*sharp, mask);
	ImageIO::saveIntensityImage(*Done, ImageIO::getDebugFileName("done.png"));
	return Done;
}

IntensityImage * add_mask(const IntensityImage &image, std::vector<float> mask){

	std::vector<float> data;
	IntensityImageStudent* cpy = new IntensityImageStudent{ image.getWidth(), image.getHeight() };
	int total = 1;
	int width = sqrt(mask.size());
	int mask_size = mask.size();
	int rowsLeft = (width -1) /2;
	total = 0;
	for (int i = 0; i < mask.size(); i++){
		total = total + mask.at(i);
	}

	std::cout << mask.size() << " " <<     width << " " << rowsLeft;
	for (int x = (image.getWidth() * rowsLeft) + rowsLeft; x < (image.getHeight() * image.getWidth()) - ((image.getWidth() * rowsLeft)); x++) {
		data.clear();
		//Bovenste rijen doen
		for (int y = 0; y < rowsLeft; y++) {
			for (int i = 0; i < width; i++){
				data.push_back(image.getPixel(x - (image.getWidth()*(rowsLeft - y)) - (rowsLeft - i)));
			}
		}
		//Middelste rij
		for (int i = 0; i < width; i++){
			data.push_back(image.getPixel((x - rowsLeft) + i));
		}
		//Onderste rijen
		for (int y = 0; y < rowsLeft; y++) {
			for (int i = 0; i < width; i++){
				data.push_back(image.getPixel(x + (image.getWidth()*(y)) - (rowsLeft - i)));
			}
		}
		//std::cout << data.size() << "datasize\n";
		if (x % image.getWidth() >=rowsLeft && x % image.getWidth() < image.getWidth() -rowsLeft){
			////////////////////////////////////////////////set the pixels
			int pixel = 0;
			for (int z = 0; z < mask_size; z++){
				pixel += (mask[z] * data[z]);

			}
			if (pixel < 0){
				pixel = 0;
			}
			if (total!=0){
				cpy->setPixel(x, Intensity(pixel/total));
			}
			else{
				cpy->setPixel(x, Intensity(pixel));
			}
		}
		else{
			int pixel = image.getPixel(x);
			cpy->setPixel(x, Intensity(pixel));
		}
	}
	ImageIO::saveIntensityImage(*cpy, ImageIO::getDebugFileName("function.png"));
	return cpy;

}
IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const {
	return nullptr;
}