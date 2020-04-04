# isogrid Houdini SOP

![A](https://media.giphy.com/media/Yrfx3lUESu9V9YG2VO/giphy.gif)
![B](https://media.giphy.com/media/dXQhYcHP9n1EVtsorT/giphy.gif)

This is a C++ port of [isogrid](https://github.com/wblut/isogrid) Processing library by [wblut](https://twitter.com/wblut) with a Houdini plugin.

## Requirements

- CMake
- C++ compiler (compatible with your Houdini version. e.g. For 16.5 you need MSVC 2015).

## Build

From the repository folder:

```
    mkdir build ; cd build
    cmake .. -DHFS="C:/Program Files/Side Effects Software/Houdini 16.5.405"
    cmake --build . --config Release
```

You additionally can set `HOUDINI_DSO_DIR` variable if your configuration folder is not default.
