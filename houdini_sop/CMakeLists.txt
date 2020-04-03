# Note: for houdini 16.5 edit HoudiniConfig.cmake at the line 45:
# replace ${_houdini_root} with ${_houdini_install_root}
# to get it compiling

list(APPEND CMAKE_PREFIX_PATH "${HFS}/toolkit/cmake")
message(STATUS ${CMAKE_PREFIX_PATH})
find_package(Houdini REQUIRED)

include_directories(include)

add_library(SOP_IsoGrid SHARED
  SOP_IsoGrid.h
  SOP_IsoGrid.cpp
)

target_link_libraries(SOP_IsoGrid PRIVATE Houdini isosystem)
target_include_directories(SOP_IsoGrid PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

if (HOUDINI_DSO_DIR)
  message(STATUS "Using custom DSO directory: ${HOUDINI_DSO_DIR}")
  houdini_configure_target(SOP_IsoGrid INSTDIR ${HOUDINI_DSO_DIR})
else()
  houdini_configure_target(SOP_IsoGrid)
endif()
