#include "StudentPreProcessing.h"
#include <math.h>
#include "Mask.hpp"
#include "ImageIO.h"
#include "IntensityImageStudent.h"
#include "RGBImageStudent.h"
#include "Point2D.h"
#include "ImageFactory.h"
#include "exectimer.h"
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
	Point2D<int> oldSize(image.getWidth(), image.getHeight());

	float x_ratio = static_cast<float>(oldSize.getX() - 1) / 200;
	float y_ratio = static_cast<float>(oldSize.getY() - 1) / 200;
	float ratio = y_ratio;
	if (x_ratio > y_ratio){ ratio = x_ratio; }

	Point2D<int> newSize(oldSize.getX() / ratio, oldSize.getY() / ratio);
	IntensityImage* result = ImageFactory::newIntensityImage(newSize.getX(), newSize.getY());
	int offset = 0;
	for (int row = 0; row < newSize.getY(); ++row) {
		for (int column = 0; column < newSize.getX(); ++column) {
			float old_X = column * ratio;
			float old_Y = row * ratio;

			int leftHigh = image.getPixel((int)old_X, (int)old_Y);//a
			int leftDown = image.getPixel((int)old_X, (int)old_Y + 1);//c
			int rightHigh = image.getPixel((int)old_X + 1, (int)old_Y); //b
			int rightDown = image.getPixel((int)old_X + 1, (int)old_Y + 1); //d
			
			float x_top = ((((int)old_X+1) - old_X) * leftHigh) + ((old_X - (int)old_X) * rightHigh);
			float x_down = ((((int)old_X + 1) - old_X) * leftDown) + ((old_X - (int)old_X) * rightDown);

			float newValue = ((((int)old_Y + 1) - old_Y) * x_top) + ((old_Y - (int)old_Y) * x_down);

			result->setPixel(column, row, Intensity(newValue));
		}
	}

	ImageIO::saveIntensityImage(*result, ImageIO::getDebugFileName("scale.png"));

	return result;
}

IntensityImage * StudentPreProcessing::stepEdgeDetection(const IntensityImage &image) const {
	std::cout << "start edged detection \n";
	std::vector<float> laplacian{ 0, 0, 0, 1, 1, 1, 0, 0, 0,
								 0, 0, 0, 1, 1, 1, 0, 0, 0 ,
								 0, 0, 0, 1, 1, 1, 0, 0, 0 ,
								 1, 1, 1, -4, -4, -4, 1, 1, 1 ,
								 1, 1, 1, -4, -4, -4, 1, 1, 1 ,
								 1, 1, 1, -4, -4, -4, 1, 1, 1 ,
								 0, 0, 0, 1, 1, 1, 0, 0, 0 ,
								 0, 0, 0, 1, 1, 1, 0, 0, 0 ,
								 0, 0, 0, 1, 1, 1, 0, 0, 0 };

	Mask m;
	IntensityImage * blur = m.add_mask(image, laplacian);
	return blur;
}
IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const {
	IntensityImage *newImage = new IntensityImageStudent(image.getWidth(), image.getHeight());
	int value = 0;
	int brightness = 0;
	for (int y = 1; y < image.getHeight() - 1; y++){
		for (int x = 1; x < image.getWidth() - 1; x++){
			brightness += image.getPixel(x, y);
		}
	}
	brightness/= image.getHeight()*image.getWidth();
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
	return newImage;
}