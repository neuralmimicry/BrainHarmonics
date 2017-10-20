cmake_minimum_required(VERSION 3.8)
project(opengl)

set(DEPS "/home/user/opengl_dev/glfw-3.2.1/deps")

include_directories(${DEPS})


set(GLAD "${DEPS}/glad/glad.h" "${DEPS}/glad.c")

FIND_PACKAGE(glfw3 REQUIRED)

add_executable(first first_glfw.cpp ${GLAD})

target_link_libraries(first glfw)

