#ifndef INTERACTIVE_H
#define INTERACTIVE_H

#include <opencv2/opencv.hpp>
#include <vector>
#include "checkpoint.h"

int getScale(cv::Mat image);
std::vector<checkpoint> getPoints(cv::Mat image);
double pixToKilometres(double pixels,int scale);

#endif
