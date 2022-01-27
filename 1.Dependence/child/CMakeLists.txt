PROJECT(child)                           #工程名
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)     #需要的最低版本

set(ObjName child)

link_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../father/lib
)

add_library(${ObjName} STATIC Child.cpp)

target_link_libraries(${ObjName}
    father
)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
