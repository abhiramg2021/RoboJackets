#ifndef STUDENT_FUNCTIONS_HPP
#include <opencv2/opencv.hpp>
cv::Mat FindColors(const cv::Mat input, const cv::Scalar range_min, const cv::Scalar range_max);
cv::Mat ReprojectToGroundPlane(const cv::Mat input, cv::Mat homograph, cv::Size map_size);
#define STUDENT_FUNCTIONS_HPP
#endif
