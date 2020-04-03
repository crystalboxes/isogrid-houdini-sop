add_library(isogrid STATIC
  include/WB_IsoHexGrid.h
  include/WB_IsoGridSegment.h
  include/WB_IsoGridCell.h
  include/WB_IsoGridLine.h
  
  src/WB_IsoHexGrid.cpp
  src/WB_IsoGridSegment.cpp
  src/WB_IsoGridCell.cpp
  src/WB_IsoGridLine.cpp
)

target_include_directories(isogrid PUBLIC include)
target_link_libraries(isogrid PRIVATE applet)
