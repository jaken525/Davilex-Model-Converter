cmake_minimum_required(VERSION 3.30)

project(DavilexConverter)

if(WIN32)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")
endif(WIN32)

add_executable(${PROJECT_NAME} DavilexConverter/DavilexConverter.cpp)

