cmake_minimum_required(VERSION 3.29) 	# Specify CMake version.
project(problem1) 			# A project name. This can be anything.
set(CMAKE_CXX_STANDARD 20) 		# Specify C++ version.

add_executable(${CMAKE_PROJECT_NAME} ${CMAKE_SOURCE_DIR}/problem1.cpp)