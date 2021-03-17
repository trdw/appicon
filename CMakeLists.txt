cmake_minimum_required(VERSION 3.17)
project(appicon)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
set(CMAKE_CXX_STANDARD 14)

add_executable(appicon main.cpp)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "appicon")
target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} )