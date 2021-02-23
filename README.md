# OpenCV
These projects use opencv 4.5.1 and are developed with c ++ & CLion

```C++
cmake_minimum_required(VERSION 3.17)
project(examen)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Where to find CMake modules and OpenCV
set(OpenCV_DIR "C:\\opencv4.5.1\\mingw_build\\install")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(examen main.cpp)

# add libs you need
set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs)

# linking
target_link_libraries(examen ${OpenCV_LIBS})
```

```Js
https://stackoverflow.com/questions/35984678/use-opencv-with-clion-ide-on-windows
```



