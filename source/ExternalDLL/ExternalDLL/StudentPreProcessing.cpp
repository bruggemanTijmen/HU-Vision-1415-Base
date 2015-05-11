#include "StudentPreProcessing.h"


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

	std::vector<float> left{ -1, -1, 0,
							-0, -1, 1,
							1, -1, 0 };

	std::vector<float> right{ -1, 0, 1,
							0, 0, -4,
							1, 0, 1 };

	std::vector<float> test1{ -1, 1, 0,
							0, 1, 1,
							1, 1, 0 };
	Mask m;
	IntensityImage * blur = m.add_mask(image, left);
	ImageIO::saveIntensityImage(*blur, ImageIO::getDebugFileName("test1.png"));
	IntensityImage * high_pass = m.add_mask(image, right);
	ImageIO::saveIntensityImage(*high_pass, ImageIO::getDebugFileName("test2.png"));
	IntensityImage * test3 = m.add_mask(image, test1);
	ImageIO::saveIntensityImage(*test3, ImageIO::getDebugFileName("test3.png"));
	
	IntensityImageStudent* sharp = new IntensityImageStudent{ image.getWidth(), image.getHeight() };
	for (int i = 0; i < blur->getHeight()*blur->getWidth();i++){ 
		int pixel = blur->getPixel(i) + high_pass->getPixel(i);
		if (pixel > 255){ pixel = 255; }
		sharp->setPixel(i, Intensity(pixel));
	}
	ImageIO::saveIntensityImage(*sharp, ImageIO::getDebugFileName("sharp.png"));
	IntensityImage* Done = m.add_mask(*sharp, mask3);
	ImageIO::saveIntensityImage(*Done, ImageIO::getDebugFileName("done.png"));
	return sharp;
}
IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const {
	return nullptr;
}