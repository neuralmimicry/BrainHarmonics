cmake_minimum_required(VERSION 3.8)
project(opengl)

set(DEPS "/home/user/opengl_dev/glfw-3.2.1/deps")
set(CMAKE_CXX_STANDARD 11)

include_directories(${DEPS})


set(GLAD "${DEPS}/glad/glad.h" "${DEPS}/glad.c")

FIND_PACKAGE(glfw3 REQUIRED)

add_executable(first first_glfw.cpp ${GLAD})
add_executable(second twod.cpp ${GLAD})
add_executable(third triangles.cpp ${GLAD})

target_link_libraries(first glfw)
target_link_libraries(second glfw)
target_link_libraries(third glfw)

