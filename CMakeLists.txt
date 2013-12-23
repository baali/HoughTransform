cmake_minimum_required (VERSION 2.6)

#name of the project
PROJECT(particle_detection)

FIND_PACKAGE(OpenCV REQUIRED)


INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIR})

LINK_DIRECTORIES(${OpenCV_LIBRARY_DIRS})

ADD_EXECUTABLE(particle_detection
cv_hough.cxx
# canny.cxx
# HoughCircle_Demo.cpp
)

TARGET_LINK_LIBRARIES(particle_detection
${OpenCV_LIBS}
)