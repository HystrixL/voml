add_executable(example example.cpp)

target_link_libraries(example PRIVATE voml)

find_package(OpenCV CONFIG REQUIRED)
target_link_libraries(example PRIVATE opencv_world)
