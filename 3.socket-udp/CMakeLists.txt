cmake_minimum_required(VERSION 2.8.9)

message(${CMAKE_CURRENT_SOURCE_DIR})  #CMakelists的位置

#链接的库的文件位置
link_directories(
     ${CMAKE_CURRENT_SOURCE_DIR}
)
#头文件路径
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)
#编译 -lpthread
set(CMAKE_CXX_FLAGS -pthread)

#编译生成库
set(SOURCES_CPP 
    ${CMAKE_CURRENT_SOURCE_DIR}/SocketUDP.cpp
)

add_library(Socket SHARED ${SOURCES_CPP}) 


#链接库生成可执行文件
set (PROJECT_LINK_LIBS 
        ${CMAKE_CURRENT_SOURCE_DIR}/libSocket.so 
        
)  #设置将要链接的库名
add_executable(demo main.cpp)
target_link_libraries(demo ${PROJECT_LINK_LIBS} )  #链接libtestStudent.so编译main.cpp生成可执行文件main。输入./main即可执行
 