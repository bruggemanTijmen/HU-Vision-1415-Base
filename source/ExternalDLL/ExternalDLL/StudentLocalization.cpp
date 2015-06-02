#include "StudentLocalization.h"
#include "ImageIO.h"
#include "intensityImageStudent.h"
#include "ImageFactory.h"

bool StudentLocalization::stepFindHead(const IntensityImage &image, FeatureMap &features) const {
	return false;
}

bool StudentLocalization::stepFindNoseMouthAndChin(const IntensityImage &image, FeatureMap &features) const {
	return false;
}

bool StudentLocalization::stepFindChinContours(const IntensityImage &image, FeatureMap &features) const {
	return false;
}

bool StudentLocalization::stepFindNoseEndsAndEyes(const IntensityImage &image, FeatureMap &features) const {
	return false;
}

bool StudentLocalization::stepFindExactEyes(const IntensityImage &image, FeatureMap &features) const {
	RGBImage * testImage = ImageFactory::newRGBImage();
	ImageIO::intensityToRGB(image, *testImage);
	Feature nose = features.getFeature(Feature::FEATURE_NOSE_BOTTOM);
	Feature head_left = features.getFeature(Feature::FEATURE_HEAD_LEFT_SIDE);
	Feature head_right = features.getFeature(Feature::FEATURE_HEAD_RIGHT_SIDE);
	Feature head_top = features.getFeature(Feature::FEATURE_HEAD_TOP);
	IntensityImageStudent * eyeLeft = new IntensityImageStudent(image.getWidth(), image.getHeight());

	//DETECT LEFT EYE
	int x_top_left = head_left.getX() + (testImage->getWidth()/ 35);
	int y_top_left = head_top.getY();
	int x_bot_left = head_top.getX();
	int y_bot_left = nose.getY(); 
	int top_i = x_top_left + (y_top_left * testImage->getWidth());
	int bot_i = x_bot_left + (y_bot_left * testImage->getWidth());
	for (int i = x_top_left; i < x_bot_left; i++){
		int pos = i - x_top_left;
		testImage->setPixel(top_i + pos, RGB(0, 255, 255));
		testImage->setPixel(bot_i - pos, RGB(0, 255, 255));
	}
	std::vector<int> histogram;
	for (int i = y_top_left; i < y_bot_left; i++){ // maak histogram
		int total = 0;
		for (int y = x_top_left; y < x_bot_left; y++){
			if (testImage->getPixel((i*testImage->getWidth()) + y).b != 255){
				total++;
			}
		}
		histogram.push_back(total);
	}
	int min = 1000000000; // minimun histogram value
	int avg = 0; //gemiddelde
	for (int i = 1; i < histogram.size()-1; i++){
		avg += histogram[i];
		if (histogram[i] < min ){
			min = histogram[i];
		}
	}
	avg = avg / histogram.size();
	bool found = false;
	int newY_bot_left = y_bot_left;
	int newY_top_left = y_bot_left;
	for (int i = histogram.size(); i > 0; i--){
		if (!found && histogram[i] == min){
			newY_bot_left = (y_bot_left - (histogram.size() - i)) ;
		}
		else if (!found && newY_bot_left != y_bot_left && histogram[i] > avg){
			found = true;
		}
		if (found){
			if (histogram[i] > avg){
				newY_top_left = (y_bot_left - (histogram.size() - i));
			}
			else{
					break;
			}
		}
	}
	histogram.clear();
	for (int x = x_top_left; x < x_bot_left; x++){
		int total = 0;
		for (int y = newY_top_left; y < newY_bot_left; y++){
			if (testImage->getPixel(x + (y * testImage->getWidth())).b != 255){
				total += 1;
			}
		}
		histogram.push_back(total);
	}

	int newX_top_left = x_top_left;
	int newX_bot_left = x_bot_left;

	bool foundleft = false;
	for (int i = 0; i < histogram.size(); i++){
		if (!foundleft && histogram[i] == 0){
			if ( histogram[i + 1] >0){
				newX_top_left = (x_top_left + i);
				foundleft = true;
				continue;
			}
		}
		if (foundleft && histogram[i] == 0){
			newX_bot_left = (x_bot_left - (histogram.size() - i));
			break;
		}
	}
	top_i = newX_top_left + (newY_top_left * testImage->getWidth());
	bot_i = newX_bot_left + (newY_bot_left * testImage->getWidth());
	for (int i = newX_top_left; i < newX_bot_left; i++){
		int pos = i - newX_top_left;
		testImage->setPixel(top_i + pos, RGB(0, 0, 255));
		testImage->setPixel(bot_i - pos, RGB(0, 0, 255));
	}

	//DETECT RIGHT EYE
	int x_top_right = head_top.getX();
	int y_top_right = head_top.getY();
	int x_bot_right = head_right.getX() - (testImage->getWidth()/20);
	int y_bot_right = nose.getY();
	top_i = x_top_right + (y_top_right * testImage->getWidth());
	bot_i = x_bot_right + (y_bot_right * testImage->getWidth());
	for (int i = x_top_right; i < x_bot_right; i++){
		int pos = i - x_top_right;
		testImage->setPixel(top_i + pos, RGB(0, 0, 255));
		testImage->setPixel(bot_i - pos, RGB(0, 0, 255));
	}
	for (int i = y_top_right; i < y_bot_right; i++){
		int total = 0;
		for (int y = x_top_right; y < x_bot_right; y++){
			if (testImage->getPixel((i*testImage->getWidth()) + y).b != 255){
				total++;
			}
		}
		histogram.push_back(total);
	}

	min = 1000000000; // minimun histogram value
	avg = 0; //gemiddelde
	for (int a : histogram){
		avg += a;
		if (a < min){
			min = a;
		}
	}
	avg = avg / histogram.size();
	std::cout << min;
	found = false;
	int newY_bot_right = y_bot_right;
	int newY_top_right = y_bot_right;
	for (int i = histogram.size(); i > 0; i--){
		if (!found && histogram[i] == min){
			newY_bot_right =  (y_bot_right - (histogram.size() - i));
		}
		else if (!found && newY_bot_right != y_bot_left && histogram[i] > avg){
			found = true;
		}
		if (found){
			if (histogram[i] > avg){
				newY_top_right = (y_bot_right  - (histogram.size() - i) );
			}
			else{
				break;
			}
		}
	}
	bot_i = x_bot_right + (newY_bot_right * image.getWidth());
	top_i = x_top_right + (newY_top_right * testImage->getWidth());
	for (int i = x_top_right; i < x_bot_right; i++){
		int pos = i - x_top_right;
		testImage->setPixel(top_i + pos, RGB(255, 255, 0));
		testImage->setPixel(bot_i - pos, RGB(255, 255, 0));
	}
	histogram.clear();
	for (int x = x_top_right; x < x_bot_right; x++){
		int total = 0;
		for (int y = newY_top_right; y < newY_bot_right; y++){
			if (testImage->getPixel(x + (y * testImage->getWidth())).r != 255){
				total += 1;
			}
		}
		histogram.push_back(total);
	}
	for (int a : histogram){
		avg += a;
		if (a < min){
			min = a;
		}
	}
	int newX_top_right = x_top_right;
	int newX_bot_right = x_bot_right;

	foundleft = false;
	for (int i = histogram.size(); i > 0; i--){
		if (!foundleft && histogram[i] == 0){
			if (histogram[i -1] >0 && histogram[i -2] > 0 && i != histogram.size()){
				newX_bot_right = (x_bot_right - (histogram.size() -i));
				foundleft = true;
				continue;
			}
		}
		if (foundleft && histogram[i] == 0){
			newX_top_right = (newX_top_right+ i );
			break;
		}
	}
	top_i = newX_top_right + (newY_top_right * testImage->getWidth());
	bot_i = newX_bot_right + (newY_bot_right * testImage->getWidth());
	for (int i = newX_top_right; i < newX_bot_right; i++){
		int pos = i - newX_top_right;
		testImage->setPixel(top_i + pos, RGB(0, 255, 0));
		testImage->setPixel(bot_i - pos, RGB(0, 255, 0));
	}
	features.getFeature(Feature::FEATURE_EYE_RIGHT_RECT);
	Feature eye(Feature::FEATURE_EYE_LEFT_RECT);
	eye.addPoint(Point2D<double>(newX_top_left,newY_top_left));
	eye.addPoint(Point2D<double>(newX_bot_left,newY_bot_left));
	features.putFeature(eye);


	Feature eye2(Feature::FEATURE_EYE_RIGHT_RECT);
	eye2.addPoint(Point2D<double>(newX_top_right, newY_top_right));
	eye2.addPoint(Point2D<double>(newX_bot_right, newY_bot_right));
	features.putFeature(eye2);

	return true;
}