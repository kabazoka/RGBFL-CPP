# Add executable with main.cpp and color_models.cpp
add_executable(RGBFL main.cpp color_models.cpp)

# Link against OpenCV libraries
target_link_libraries(RGBFL ${OpenCV_LIBS})
