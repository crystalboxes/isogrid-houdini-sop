cmake_minimum_required(VERSION 3.12)
project(isogrid_test)

option(BUILD_TEST_EXECUTABLE "Build test executable" OFF)
option(BUILD_HOUDINI_SOP "Build Houdini SOP" ON)

if(NOT HFS)
  set(BUILD_HOUDINI_SOP OFF)
  message(STATUS "Skipping Houdini plugin build, HFS variable is not set.")
endif()

add_subdirectory(isogrid)

if (BUILD_TEST_EXECUTABLE)
  add_executable(isogrid_test test.cpp)
  target_link_libraries(isogrid_test PRIVATE isosystem)
  target_compile_definitions(isogrid_test PRIVATE WRITEOBJ=1)
endif()

if (BUILD_HOUDINI_SOP)
  add_subdirectory(houdini_sop)
endif()
