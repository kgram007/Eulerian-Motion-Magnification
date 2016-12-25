#********************************************************************
#
#	File Name:      EulerianMotionMag.cpp
#	Author:         Ramsundar K G (ramsundar@asu.edu)
#	Date:           December 22, 2016
#
#	Description:    CMakeList file
#
#********************************************************************

# CMake version check
cmake_minimum_required(VERSION 2.8)

# Project Name
project(Eulerian_Motion_Magnification)

# Dependent packages
find_package(OpenCV REQUIRED core imgproc objdetect highgui)
find_package(Boost REQUIRED program_options)
find_package(OpenMP)

# Using CXX Flags: Optimization (-O3) and OpenMP 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -fopenmp -std=c++11")

# Includes
include_directories("include")
include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories( ${Boost_INCLUDE_DIRS} )

# Executable file directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# Executable
add_executable(${PROJECT_NAME}
	src/main.cpp
	src/EulerianMotionMag.cpp
	
	include/EulerianMotionMag.h
	include/Timer.h
)

# Link libraries
target_link_libraries(${PROJECT_NAME}
	${OpenCV_LIBS}
	${OpenMP_LIBS}
	${Boost_LIBRARIES}
)
