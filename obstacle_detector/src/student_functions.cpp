#include "student_functions.hpp"

cv::Mat FindColors(const cv::Mat input, const cv::Scalar range_min, const cv::Scalar range_max){
    cv::Mat input_hsv;
    cv::cvtColor(input, input_hsv, cv::COLOR_BGR2HSV);
    cv::Mat output(input.size(), CV_8UC1); // one channel 8 bit
    for (int r = 0; r < input_hsv.rows; r++){
        for (int c = 0; c < input_hsv.cols; c++){
            const auto input_color = input_hsv.at<cv::Vec3b>(r,c); // grab color from this position on the image
            if ((input_color[0] >= range_min[0] && input_color[0] <= range_max[0]) && 
                (input_color[1] >= range_min[1] && input_color[1] <= range_max[1]) &&
                (input_color[2] >= range_min[2] && input_color[2] <= range_max[2])){
                    output.at<uint8_t>(r,c) = 255;
                }
            else {
                output.at<uint8_t>(r,c) = 0;
            }
        }
    }
    return output;
}

cv::Mat ReprojectToGroundPlane(const cv::Mat input, cv::Mat homography, cv::Size map_size){
    cv::Mat output(map_size, CV_8UC1);
    
    for(int r = 0; r < output.rows -1; r++){
        for(int c = 0; c < output.cols - 1; c++){
            cv::Vec3d dest_vec(r,c,1);
            cv::Vec3d src_vec = cv::Mat1d(homography.inv() * dest_vec);
            cv::Point2i dest_point(r,c);
            cv::Point2i src_point(src_vec[0]/src_vec[2], src_vec[1]/src_vec[2]);
            //above line normalizes the values src point
            if(src_point.inside(cv::Rect(cv::Point(), input.size()))){
                output.at<uint8_t>(dest_point) = input.at<uint8_t>(src_point);
            } else{
                output.at<uint8_t>(dest_point) = 127;
            }
        }
    }
    return output;


}