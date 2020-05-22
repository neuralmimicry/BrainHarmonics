cmake_minimum_required(VERSION 2.8.9)
#set(CMAKE_CXX_COMPILER "/home/shashi/opt/openmpi/bin/mpic++")
project(mpitest)
 
#Bring the headers, such as CommIntf.h into the project
include_directories(include)
 
#the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.cpp")
 
add_executable(testMpi ${SOURCES})
