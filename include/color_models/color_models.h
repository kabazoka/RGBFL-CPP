#pragma once
#include <iostream>
#include <cmath>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video.hpp>
#include <cstdlib> 
#include <ctime>   
#include <time.h>
#include<math.h>
#include<fstream>
#define D65
#define radian CV_PI/180.0

//color translate
void RGB_2_sRGB(cv::Mat& img);
void sRGB_2_RGB(cv::Mat& img);
void K3_RGB_2_sRGB(cv::Mat& img,float maximum);
void xyY_2_sBGR(cv::Mat& img);
void XYZ_2_sBGR(cv::Mat& img);
void XYZ_2_BGR(cv::Mat& img);
void Yxy_2_RGB(cv::Mat& img);
void RGB_2_xyY(cv::Mat& img);
void linearRGB2XYZ_img(cv::Mat& img);
void linearRGB2XYZ(float R, float G, float B, float* X, float* Y, float* Z);
void XYZ2Lab(float X, float Y, float Z, float* L, float* a, float* b);
void XYZ2Lab_Could_negative(float X, float Y, float Z, float* L, float* a, float* b);//KD
void Mat_XYZ2Lab(cv::Mat str, cv::Mat& out);//KD
void XYZ2Lab_refWhite(cv::Vec3f inputXYZ, cv::Vec3f ReferenceWhiteXYZ, cv::Vec3f& OutputLab); //KD
void Mat_XYZ2Lab_RfWhite(cv::Mat str, cv::Vec3f ReferenceWhiteXYZ, cv::Mat& out);//KD
void Lab2XYZ_RfWhite(cv::Vec3f inputLab, cv::Vec3f ReferenceWhiteXYZ, cv::Vec3f& OutputXYZ);//KD
void Vec_Lab2XYZ(std::vector<std::vector<cv::Vec3f>>& input_Lab);//KD
void Vec_Lab2XYZ_RfWhite(std::vector<std::vector<cv::Vec3f>>& input_Lab, cv::Vec3f ReferenceWhiteXYZ);//KD
void XYZ2Lab_no_limit(float X, float Y, float Z, float* L, float* a, float* b);
void Linear2RGBLab(cv::Mat str, cv::Mat& out);
void LinearRGB2LinearLab(cv::Mat str, cv::Mat& out);
void XYZ2LinearsRGB(float X, float Y, float Z, float* R, float* G, float* B);
void Lab2XYZ(float L, float a, float b, float* X, float* Y, float* Z);
void Lab2LinearsRGB(cv::Mat& bmp_img, cv::Mat lab_img);
void Lab2LCH(cv::Mat img, cv::Mat& out);
void LCH2Lab(cv::Mat img, cv::Mat& out);
void XYZ_normalize_refW(cv::Mat img, cv::Mat &out, cv::Vec3f White_point);
void XYZ2OkLab(cv::Mat img, cv::Mat& out);
void LinearsRGB2OkLab(cv::Mat img, cv::Mat& out);
void OkLab2LinearRGB(cv::Mat img, cv::Mat& out);
void OkLab2XYZ(cv::Vec3f Lab, cv::Vec3f& XYZ);
void Vec_OkLab2XYZ(std::vector<std::vector<cv::Vec3f>>& input_OkLab);

//Caculate delta E2000
double CIEdeltaE2000(cv::Vec3f color_Lab1, cv::Vec3f color_Lab2);

