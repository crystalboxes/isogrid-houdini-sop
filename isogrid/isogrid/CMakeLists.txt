add_library(isogrid STATIC
  include/WB_IsoHexGrid.h
  include/WB_IsoGridSegment.h
  include/WB_IsoGridCell.h
  include/WB_IsoGridLine.h
  include/WB_CubeGridExporter.h
  
  src/WB_IsoHexGrid.cpp
  src/WB_IsoGridSegment.cpp
  src/WB_IsoGridCell.cpp
  src/WB_IsoGridLine.cpp

  src/WB_CubeGridExporter.cpp
)

target_include_directories(isogrid PUBLIC include)
target_link_libraries(isogrid PRIVATE applet)
