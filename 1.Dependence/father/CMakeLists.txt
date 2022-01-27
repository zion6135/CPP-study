PROJECT(father)                           #工程名
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)     #需要的最低版本

set(ObjName father)
add_library(${ObjName} STATIC father.cpp)


set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
