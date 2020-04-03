add_library(applet STATIC
  include/applet.h
  include/typedef.h
  include/noise.h
  src/applet.cpp
)
target_include_directories(applet PUBLIC include)
