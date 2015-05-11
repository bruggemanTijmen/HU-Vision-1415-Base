#include "StudentLocalization.h"
#include "ImageIO.h"
#include "intensityImageStudent.h"
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
	//return false;
	std::cout << "mekeksesss\n\n\n\n\n\n";
	Feature nose = features.getFeature(Feature::FEATURE_NOSE_BOTTOM);
	Feature head_left = features.getFeature(Feature::FEATURE_HEAD_LEFT_SIDE);
	Feature head_right = features.getFeature(Feature::FEATURE_HEAD_RIGHT_SIDE);
	Feature head_top = features.getFeature(Feature::FEATURE_HEAD_TOP);
	IntensityImageStudent * eyeLeft = new IntensityImageStudent(image.getWidth(), image.getHeight());


	ImageIO::saveIntensityImage(image, ImageIO::getDebugFileName("muis.jpg"));
	features.getFeature(Feature::FEATURE_EYE_RIGHT_RECT);
	Feature eye(Feature::FEATURE_EYE_LEFT_RECT);
	std::cout << "head left = " << head_left.getX() << " - " << head_left.getY() << "\n";
	std::cout << "nose = " << nose.getX() << " - " << nose.getY() << "\n";
	eye.addPoint(Point2D<double>(head_left.getX(),head_left.getY()-10));
	eye.addPoint(Point2D<double>(nose.getX(),nose.getY()));
	features.putFeature(eye);

	for (Point2D<double> p : eye.getPoints()){
		std::cout << "Point: " << p.getX() << " - " << p.getY() << "\n";
	}
	std::cout << "size = " << eye.getPoints().size() << "\n";



	Feature eye2(Feature::FEATURE_EYE_RIGHT_RECT);
	eye2.addPoint(Point2D<double>(40, 40));
	eye2.addPoint(Point2D<double>(60, 60));
	features.putFeature(eye2);
	for (Point2D<double> p : eye2.getPoints()){
		std::cout << "Point12: " << p.getX() << " - " << p.getY() << "\n";
	}
	std::cout << "size = " << eye2.getPoints().size();

	Feature b = features.getFeature(Feature::FEATURE_EYE_RIGHT_RECT);
	std::cout << "  =  " << b.getX() << " - " << b.getY() << "\n";
	return true;
}