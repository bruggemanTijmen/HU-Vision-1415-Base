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

	IntensityImageStudent* IntensityImage = new IntensityImageStudent{ image.getWidth(), image.getHeight() };

	const int Gaussian_mask[] = { 0, 1, 0,
								  1, -4, 1,
								  0, 1, 0 };

	const int OFFSET = 10;
	
	for (int i = image.getWidth() + 1; i < (image.getHeight() * image.getWidth()) - ((image.getWidth() +1)+ image.getWidth()); i++) {

		if (i % image.getWidth() == 0 || i % image.getWidth() == image.getWidth()-1){
			continue;
		}
		IntensityImage->setPixel(i, Intensity{ 255 });	
	}

	ImageIO::saveIntensityImage(image, ImageIO::getDebugFileName("C:\\Users\\Patrick\\Documents\\GitHub\\HU-Vision-1415-Base\\debug\\test.png"));

	return IntensityImage;
}

IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const {
	return nullptr;
}