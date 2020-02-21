cmake_minimum_required(VERSION 3.0)

project(asciivis)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_executable(test_unicode_out test/test_unicode_out.cpp
	)
add_test(test_unicode_out_test test_unicode_out)

add_executable(test_asciivis test/test_asciivis.cpp
	src/asciivis.cpp)
add_test(test_asciivis_test test_asciivis)
