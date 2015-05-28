#include "StudentPreProcessing.h"
#include <math.h>

#include "Mask.hpp"
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

IntensityImage * StudentPreProcessing::stepEdgeDetection(const IntensityImage &image) const {
	std::cout << "student edge detection started\n";
	std::vector<float>mask = { 0, 0, -1, -2, -1, 0, 0, //////////la placien
								0, -2, -3, -4, -3, -2, 0,
								-1, -3, 1, 9, 1, -3, -1,
								-2, -4, 9, 22, 9, -4, -2,
								-1, -3, 1, 9, 1, -3, -1,
								0, -2, -3, -4, -3, -2, 0,
								0, 0, -1, -2, -1, 0, 0 };

	std::vector<float> mask3 = { -0.5, -1, -0.5,
		-1, 6, -1,
		-0.5, -1, -0.5 };

	std::vector<float> mask5 = { 0, 1, 0,
								1, -4, 1,
								-0, 1, 0};
	std::vector<float> mask100{ 0, 0, 0, 1, 1, 1, 0, 0, 0,
								 0, 0, 0, 1, 1, 1, 0, 0, 0 ,
								 0, 0, 0, 1, 1, 1, 0, 0, 0 ,
								 1, 1, 1, -4, -4, -4, 1, 1, 1 ,
								 1, 1, 1, -4, -4, -4, 1, 1, 1 ,
								 1, 1, 1, -4, -4, -4, 1, 1, 1 ,
								 0, 0, 0, 1, 1, 1, 0, 0, 0 ,
								 0, 0, 0, 1, 1, 1, 0, 0, 0 ,
								 0, 0, 0, 1, 1, 1, 0, 0, 0 };
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
	std::vector<float> laplacian{ 1, 1, 1, 1, 1,
								 1, 1, 1, 1, 1,
								 1, 1, -24, 1, 1,
								 1, 1, 1,1, 1,
								 1, 1, 1, 1, 1 };

	std::vector<float> left{ -1, -2, -1,
							0, 0, 0,
							1, 2, 1 };

	std::vector<float> right{ -1, 0, 1,
							-2, 0, 2,
							-1, 0, 1 };

	std::vector<float> test1{ 1, 2, 1,
							2, 4, 2,
							1, 2, 1 };

	std::vector<float> nieuw{	0, 0, 0, 
								1, 1, 1,
								0, 0, 0 };
	std::vector<float> nieuw2 {		1, 1, 1,
									-4, -4, -4,
									1, 1, 1 };
	Mask m;
	IntensityImage * blur = m.add_mask(image, mask100);
	ImageIO::saveIntensityImage(*blur, ImageIO::getDebugFileName("blur.png"));/*
	IntensityImage * left_image = m.add_mask(*blur, mask100);
	ImageIO::saveIntensityImage(*left_image, ImageIO::getDebugFileName("left.png"));
	IntensityImage * right_image = m.add_mask(*blur, right);
	ImageIO::saveIntensityImage(*right_image, ImageIO::getDebugFileName("right.png"));

	IntensityImageStudent* sharp = new IntensityImageStudent{ image.getWidth(), image.getHeight() };
	for (int i = 0; i < blur->getHeight()*blur->getWidth(); i++){
		int pixel = sqrt((right_image->getPixel(i) * right_image->getPixel(i)) + (left_image->getPixel(i)*left_image->getPixel(i)));
		if (pixel > 255){
			pixel = 255;
		}
		sharp->setPixel(i, Intensity((pixel)));
	}
	ImageIO::saveIntensityImage(*sharp, ImageIO::getDebugFileName("sharp.png"));*/

	return blur;
}
IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const {
	std::cout << "student thresholding started\n";
	ImageIO::saveIntensityImage(image, ImageIO::getDebugFileName("threshhold1.png"));
	IntensityImage *newImage = new IntensityImageStudent(image.getWidth(), image.getHeight());
	int value = 0;
	int brightness = 0;
	for (int y = 1; y < image.getHeight() - 1; y++){
		for (int x = 1; x < image.getWidth() - 1; x++){
			brightness += image.getPixel(x, y);
		}
	}
	brightness/= image.getHeight()*image.getWidth();
	std::cout << "brightness: " << brightness << "\n";
	for (int y = 0; y < image.getHeight(); y++){
		for (int x = 0; x < image.getWidth(); x++){
			value = image.getPixel(x, y);
			if (value >=210 ) {
				value = 0;
			}
			else {
				value = 255;
			}
			newImage->setPixel(x, y, value);
		}
	}
	ImageIO::saveIntensityImage(*newImage, ImageIO::getDebugFileName("threshhold.png"));
	return newImage;
}