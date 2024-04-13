project(
  MSDFLib
  VERSION 1.0.1
  DESCRIPTION "MSDF atlas gen libaray"
  LANGUAGES CXX)

file(GLOB_RECURSE msdf_sources CONFIGURE_DEPENDS "./src/*.cpp")

add_library(MSDFLib ${msdf_sources})
target_include_directories(MSDFLib PUBLIC include/)

set_target_properties(MSDFLib PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(MSDFLib PROPERTIES SOVERSION 1)

FetchContent_Declare(
  freetype
  GIT_REPOSITORY https://github.com/freetype/freetype.git
  GIT_TAG VER-2-13-2)
FetchContent_Declare(
  lodepng
  GIT_REPOSITORY https://github.com/lvandeve/lodepng.git
  GIT_TAG master)
FetchContent_Declare(
  tinyxml2
  GIT_REPOSITORY https://github.com/leethomason/tinyxml2.git
  GIT_TAG 10.0.0)

set(FT_DISABLE_BROTLI
    ON
    CACHE BOOL "" FORCE)
set(FT_DISABLE_BZIP2
    ON
    CACHE BOOL "" FORCE)
set(FT_DISABLE_PNG
    ON
    CACHE BOOL "" FORCE)
set(FT_DISABLE_ZLIB
    ON
    CACHE BOOL "" FORCE)
set(FT_DISABLE_HARFBUZZ
    ON
    CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(freetype)
FetchContent_MakeAvailable(lodepng)
FetchContent_MakeAvailable(tinyxml2)

target_link_libraries(MSDFLib PUBLIC freetype lodepng tinyxml2)
target_include_directories(MSDFLib PUBLIC ${freetype_SOURCE_DIR}/include ${lodepng_SOURCE_DIR})
