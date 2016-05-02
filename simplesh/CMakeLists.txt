project(simplesh)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES TaskReader.cpp TaskReader.h main.cpp Task.h Utils.h)

add_executable(simplesh ${SOURCE_FILES})
