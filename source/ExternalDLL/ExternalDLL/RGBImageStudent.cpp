#include "RGBImageStudent.h"

RGBImageStudent::RGBImageStudent() : RGBImage() {
	//int throwError = 0, e = 1 / throwError; //Throws error without the need to include a header
	//TODO: Nothing
}

RGBImageStudent::RGBImageStudent(const RGBImageStudent &other) : RGBImage(other.getWidth(), other.getHeight()) {
	//int throwError = 0, e = 1 / throwError;

	RGBImageStudent cpy = other;
	delete[] pixel_map;
	pixel_map = cpy.getPixels();
}

RGBImageStudent::RGBImageStudent(const int width, const int height) : RGBImage(width, height) {
	//int throwError = 0, e = 1 / throwError;

	delete[] pixel_map;
	pixel_map = new RGB[width * height];
	//TODO: Initialize pixel storage
}

RGBImageStudent::~RGBImageStudent() {
	//int throwError = 0, e = 1 / throwError;
	delete[] pixel_map;
	//TODO: delete allocated objects
}

void RGBImageStudent::set(const int width, const int height) {
	RGBImage::set(width, height);
	//int throwError = 0, e = 1 / throwError;

	delete[] pixel_map;
	pixel_map = new RGB[width * height];

	//TODO: resize or create a new pixel storage (Don't forget to delete the old storage)
}

void RGBImageStudent::set(const RGBImageStudent &other) {
	RGBImage::set(other.getWidth(), other.getHeight());
	//int throwError = 0, e = 1 / throwError;

	RGBImageStudent cpy = other;
	pixel_map = cpy.getPixels();

	//TODO: resize or create a new pixel storage and copy the object (Don't forget to delete the old storage)
}

void RGBImageStudent::setPixel(int x, int y, RGB pixel) { //crash
	//int throwError = 0, e = 1 / throwError;
	//TODO: no comment needed :)
	int i = x + (y*this->getWidth());
	setPixel(i, pixel);
}

void RGBImageStudent::setPixel(int i, RGB pixel) {
	//int throwError = 0, e = 1 / throwError;
	pixel_map[i] = pixel;
	/*
	* TODO: set pixel i in "Row-Major Order"
	*
	*
	* Original 2d image (values):
	* 9 1 2
	* 4 3 5
	* 8 7 8
	*
	* 1d representation (i, value):
	* i		value
	* 0		9
	* 1		1
	* 2		2
	* 3		4
	* 4		3
	* 5		5
	* 6		8
	* 7		7
	* 8		8
	*/
}

RGB RGBImageStudent::getPixel(int x, int y) const { //crash
	//int throwError = 0, e = 1 / throwError;
	
	int i = x + (y*this->getWidth());

	return getPixel(i);	
}

RGB RGBImageStudent::getPixel(int i) const {
	//int throwError = 0, e = 1 / throwError;
	//TODO: see setPixel(int i, RGB pixel);
	return pixel_map[i];
}

RGB* RGBImageStudent::getPixels() {
	return this->pixel_map;
}

