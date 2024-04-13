project(lodepng LANGUAGES CXX)

file(GLOB lodepng_src "src/*.cpp")
add_library(lodepng ${lodepng_src})

target_include_directories(lodepng PUBLIC include/)
