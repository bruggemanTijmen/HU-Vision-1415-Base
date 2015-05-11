#pragma once
#include "IntensityImage.h"
#include <vector>
#include "IntensityImageStudent.h"
#include <iostream>
#include "ImageIO.h"

class Mask{

public:
	IntensityImage * add_mask(const IntensityImage &image, std::vector<float> mask){
		std::vector<float> data;
		IntensityImageStudent* cpy = new IntensityImageStudent{ image.getWidth(), image.getHeight() };
		int total = 1;
		int width = sqrt(mask.size());
		int mask_size = mask.size();
		int rowsLeft = (width - 1) / 2;
		total = 0;
		for (int i = 0; i < mask.size(); i++){
			total = total + mask.at(i);
		}
		std::cout << mask.size() << " " << width << " " << rowsLeft;
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
			if (x % image.getWidth() >= rowsLeft && x % image.getWidth() < image.getWidth() - rowsLeft){
				////////////////////////////////////////////////set the pixels
				int pixel = 0;
				for (int z = 0; z < mask_size; z++){
					pixel += (mask[z] * data[z]);

				}
				if (pixel < 0){
					pixel = 0;
				}
				if (total != 0){
					cpy->setPixel(x, Intensity(pixel / total));
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
};