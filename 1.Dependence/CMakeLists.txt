PROJECT(test)    
set(ObjName TestMain)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)     #需要的最低版本

set(CMAKE_CXX_FLAGS "-Wall -g -O0 -fno-builtin")

link_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/father/lib
    ${CMAKE_CURRENT_SOURCE_DIR}/child/lib
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/father
    ${CMAKE_CURRENT_SOURCE_DIR}/child
)

ADD_EXECUTABLE(${ObjName} main.cpp)        

target_link_libraries(${ObjName}
    father
    child
    
    )
    