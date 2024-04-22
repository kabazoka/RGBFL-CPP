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
#include <vector>
#include <sstream>
#include <map>

// Include color models header file
#include "color_models/color_models.h" // Include your color models header file

// Namespace for convenience
using namespace std;
namespace fs = filesystem;

// Function prototypes
cv::Vec3b bgrToLab(const cv::Vec3b& bgr);
vector<vector<double>> readFrontLightCombinations(const string& file_path);
map<string, Eigen::MatrixXf> readColorMeasurementData(const string& filePath);
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
    string dataFilePath = "../input/data/i1_8colors_27FL_v1.csv";
    
    // Read the color measurement data from the file and process Delaunay triangulation to interpolate colors
    map<string, Eigen::MatrixXf> colorData = readColorMeasurementData(dataFilePath);

    auto FL_pts_all = readFrontLightCombinations(dataFilePath);
    
    // Example to print the results
    for (const auto& pts : FL_pts_all) {
        cout << "R: " << pts[0] << ", G: " << pts[1] << ", B: " << pts[2] << endl;
    }

    // Check if the image directory exists
    if (!fs::exists(imageFolderPath)) {
        cout << "Cannot access to the directory: " << imageFolderPath << endl;
        return 1; // Exit with an error code
    }
    // // Example file iteration using filesystem (to replace the Python main loop)
    // for (const auto& entry : fs::directory_iterator(imageFolderPath)) {
    //     string imagePath = entry.path().string();
    //     // Example logging
    //     cout << "Processing image: " << imagePath << endl;

    //     // Call your processing functions here

    // }

    return 0;
}

// Function implementations
cv::Vec3b bgrToLab(const cv::Vec3b& bgr) {
    // Direct translation of the bgr_to_lab function
}

vector<vector<double>> readFrontLightCombinations(const string& file_path) {
    std::ifstream file(file_path);
    std::vector<double> FL_red, FL_green, FL_blue;
    
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << file_path << std::endl;
        return {}; // Return an empty vector if file opening fails
    }

    std::string line;
    // Skip the header line
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string cell;
        std::vector<std::string> rowData;

        // Extract each cell in the row
        while (std::getline(ss, cell, ',')) {
            rowData.push_back(cell);
        }

        // Check for enough columns and ignore rows that don't have the expected data
        if (rowData.size() > 3) { // Assuming FL_R, FL_G, and FL_B are the first three valid columns
            double value;
            for (int i = 0; i < 3; ++i) { // Only iterate over the first three values (FL_R, FL_G, FL_B)
                std::istringstream iss(rowData[i]); // Use istringstream for conversion
                
                if (iss >> value) { // Try to read a double value from the string
                    switch(i) {
                        case 0: FL_red.push_back(value); break;
                        case 1: FL_green.push_back(value); break;
                        case 2: FL_blue.push_back(value); break;
                    }
                } else {
                    // Handle the case where conversion fails, e.g., log an error or assign a default value
                    std::cerr << "Conversion failed for value: " << rowData[i] << " in row: " << line << std::endl;
                }
            }
        }
    }

    std::vector<std::vector<double>> FL_pts_all;
    // Assuming the vectors are of equal length
    for (size_t i = 0; i < FL_red.size(); ++i) {
        FL_pts_all.push_back({FL_red[i], FL_green[i], FL_blue[i]});
    }

    return FL_pts_all;
}

map<string, Eigen::MatrixXf> readColorMeasurementData(const string& filePath) {
    // Implement reading the color measurement data from the Excel file
}

vector<cv::Vec3f> readImage(const string& imagePath) {
    // Implement reading and processing an image into lab colors
}

tuple<float, float, float> interpolateColor(/* Parameters for interpolation */) {
    // Implement color interpolation logic, possibly using Eigen for matrix operations
}

// Implement other functions as needed
