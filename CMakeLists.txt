cmake_minimum_required(VERSION 3.25.0)
project(
  MSDF
  VERSION 1.0.1
  LANGUAGES CXX)

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(
    FATAL_ERROR
      "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
  )
endif()

include(FetchContent)

include("cmake/Cache.cmake")
include("cmake/CompilerWarnings.cmake")
include("cmake/StaticAnalyzers.cmake")
include("cmake/InterproceduralOptimization.cmake")

option(MSDF_ENABLE_IPO "Enable IPO/LTO" OFF)
option(MSDF_ENABLE_CACHE "Enable ccache" OFF)
option(MSDF_WARNINGS_AS_ERRORS "Treat Warnings As Errors" OFF)
option(MSDF_ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" OFF)
option(MSDF_ENABLE_SANITIZER_LEAK "Enable leak sanitizer" OFF)
option(MSDF_ENABLE_SANITIZER_UNDEFINED "Enable undefined sanitizer" OFF)
option(MSDF_ENABLE_SANITIZER_THREAD "Enable thread sanitizer" OFF)
option(MSDF_ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" OFF)
option(MSDF_ENABLE_TOOL "Enable building of atlas eneration executable" ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

if(MSDF_ENABLE_IPO)
  enable_ipo()
endif()

if(MSDF_ENABLE_CACHE)
  enable_cache()
endif()

add_subdirectory("deps")
add_subdirectory("lib")

if(MSDF_ENABLE_TOOL)
  add_subdirectory("atlas-gen")
endif()

set_project_warnings(MSDFLib ${MSDF_WARNINGS_AS_ERRORS} "" "" "")

if(MSDF_ENABLE_TOOL)
  set_project_warnings(msdf-atlas-gen ${MSDF_WARNINGS_AS_ERRORS} "" "" "")
endif()

enable_sanitizers(
  MSDFLib ${MSDF_ENABLE_SANITIZER_ADDRESS} ${MSDF_ENABLE_SANITIZER_LEAK}
  ${MSDF_ENABLE_SANITIZER_UNDEFINED} ${MSDF_ENABLE_SANITIZER_THREAD}
  ${MSDF_ENABLE_SANITIZER_MEMORY})

if(MSDF_ENABLE_TOOL)
  enable_sanitizers(
    msdf-atlas-gen ${MSDF_ENABLE_SANITIZER_ADDRESS}
    ${MSDF_ENABLE_SANITIZER_LEAK} ${MSDF_ENABLE_SANITIZER_UNDEFINED}
    ${MSDF_ENABLE_SANITIZER_THREAD} ${MSDF_ENABLE_SANITIZER_MEMORY})
endif()
