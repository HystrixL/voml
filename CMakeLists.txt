file(GLOB_RECURSE srcs CONFIGURE_DEPENDES src/*.cpp)
add_library(voml OBJECT ${srcs})
target_include_directories(voml PUBLIC include toml11)

find_package(OpenCV CONFIG REQUIRED)
target_link_libraries(voml PRIVATE opencv_world)



if (voml_BUILD_EXAMPLE)
    add_subdirectory(example)
endif ()