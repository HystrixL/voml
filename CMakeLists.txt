cmake_minimum_required(VERSION 3.5)
project(voml LANGUAGES CXX)

find_package(OpenCV REQUIRED)
set(LINKER_LANGUAGE CXX)

add_library(${PROJECT_NAME} OBJECT ./voml.hpp ./details.hpp ./opencv.hpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR} ${OpenCV_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} )

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)