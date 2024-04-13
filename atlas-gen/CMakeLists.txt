project(
  msdf-atlas-gen
  VERSION 1.0.0
  LANGUAGES CXX)

file(GLOB_RECURSE tool_sources CONFIGURE_DEPENDS "./src/*.cpp")

add_executable(msdf-atlas-gen ${tool_sources})
target_include_directories(msdf-atlas-gen PUBLIC include/)

set_target_properties(msdf-atlas-gen PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(msdf-atlas-gen PROPERTIES SOVERSION 1)

target_link_libraries(msdf-atlas-gen PRIVATE MSDFLib)
target_include_directories(msdf-atlas-gen PRIVATE MSDFLib)
