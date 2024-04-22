// Include opencv header file for image processing
#include <opencv2/opencv.hpp>
// Include Eigen library for matrix operations
#include <Eigen/Dense>
// Include filesystem library for file operations
#include <filesystem>
// Parallel computing facilities
#include <thread>
#include <future>
#include <vector>
// For logging
#include <iostream>
#include <fstream>
// General purpose libraries
#include <string>

// Include color models header file
#include "color_models/color_models.h" // Include your color models header file

// Namespace for convenience
using namespace std;
namespace fs = filesystem;

// Function prototypes
cv::Vec3b bgrToLab(const cv::Vec3b& bgr);
Eigen::MatrixXf readColorMeasurementDataCombined(const string& filePath);
map<string, Eigen::MatrixXf> readColorMeasurementDataSeparate(const string& filePath);
vector<cv::Vec3f> readImage(const string& imagePath);
tuple<float, float, float> interpolateColor(/* Parameters for interpolation */);
void plotInterpolatingFLCombinations(/* Parameters for plotting */);
// More function prototypes as per your Python script's functions

int main(int argc, char* argv[]) {
    if (argc != 1) {
        cout << "Usage: " << argv[0] << endl;
        return 1; // Exit with an error code
    }
    
    // Parse command line arguments or configure paths as needed
    string imageFolderPath = "../input/image";
    string dataFilePath = "../input/excel/i1_8colors_27FL_v1.xlsx";
    


    // Check if the directory exists
    if (!fs::exists(imageFolderPath)) {
        cout << "Cannot access to the directory: " << imageFolderPath << endl;
        return 1; // Exit with an error code
    }
    // Example file iteration using filesystem (to replace the Python main loop)
    for (const auto& entry : fs::directory_iterator(imageFolderPath)) {
        string imagePath = entry.path().string();
        // Example logging
        cout << "Processing image: " << imagePath << endl;

        // Call your processing functions here

    }

    return 0;
}

// Function implementations
cv::Vec3b bgrToLab(const cv::Vec3b& bgr) {
    // Direct translation of the bgr_to_lab function
}

Eigen::MatrixXf readColorMeasurementData(const string& filePath) {
    // Adapt Python pandas functionality to read and process Excel file data
    // You might use a C++ library for Excel file handling or convert the data to a more C++-friendly format
}

map<string, Eigen::MatrixXf> readColorMeasurementDataSeparate(const string& filePath) {
    // Similar to readColorMeasurementDataCombined, but separate data as per Python function
}

vector<cv::Vec3f> readImage(const string& imagePath) {
    // Implement reading and processing an image into lab colors
}

tuple<float, float, float> interpolateColor(/* Parameters for interpolation */) {
    // Implement color interpolation logic, possibly using Eigen for matrix operations
}

// Implement other functions as needed
