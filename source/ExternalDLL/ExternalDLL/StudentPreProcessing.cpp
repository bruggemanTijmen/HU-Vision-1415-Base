#include "StudentPreProcessing.h"
#include "IntensityImageStudent.h"
#include "ImageIO.h"

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
	printf("mekmek");
	IntensityImageStudent* cpy = new IntensityImageStudent{ image.getWidth(), image.getHeight() };

	const float Gaussian_mask[] = { 0.5, 1, 0.5,
								  1, -6, 1,
								  0.5, 1, 0.5 };

	const int OFFSET = 10;
	int width = image.getWidth();
	for (int i = image.getWidth() + 1; i < (image.getHeight() * image.getWidth()) - ((image.getWidth() +1)); i++) {

		if (i % image.getWidth() == 0 || i % image.getWidth() == image.getWidth()-1){
			continue;
		}
		
		int data[] = { image.getPixel(i - (width + 1)), image.getPixel(i - width), image.getPixel(i - (width - 1)),
			image.getPixel(i - 1), image.getPixel(i), image.getPixel(i + 1), image.getPixel(i + (width - 1)),
			image.getPixel(i + width), image.getPixel(i + (width + 1)) };
		
		Intensity pixel(255);
		int total;
		for(int x = 0; x < 9; x++){
			pixel += (Gaussian_mask[x] * data[x]);
		}
		cpy->setPixel(i, pixel);
	}

	ImageIO::saveIntensityImage(*cpy, ImageIO::getDebugFileName("testss1.png"));

	return cpy;
}

IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const {
	return nullptr;
}