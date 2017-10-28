cmake_minimum_required(VERSION 3.8)
project(opengl)

set(CMAKE_CXX_STANDARD 11)

message(${PROJECT_SOURCE_DIR}/common)
include_directories(${PROJECT_SOURCE_DIR}/common)
include_directories("/home/user/glfw-3.2.1/deps")

set(GLAD "/home/user/glfw-3.2.1/deps/glad.c" "/home/user/glfw-3.2.1/deps/glad/glad.h")

FIND_PACKAGE(OpenGL REQUIRED)
FIND_PACKAGE(glfw3 REQUIRED)
FIND_PACKAGE(GLEW REQUIRED)


include_directories(${OPENGL_INCLUDE_DIRS})



add_executable(twod twod.cpp ${GLAD})

add_executable(wave wave.cpp ${GLAD})

add_executable(transition_text transition_text.cpp ${GLAD})

add_executable(mainshader mainshader.cpp ${GLAD})

add_executable(triangles triangles.cpp ${GLAD})

add_executable(first_glfw first_glfw.cpp ${GLAD})

add_executable(scrap scrap.cpp ${GLAD})





target_link_libraries(twod glfw)

target_link_libraries(wave glfw)

target_link_libraries(transition_text glfw)

target_link_libraries(mainshader glfw)

target_link_libraries(triangles glfw)

target_link_libraries(first_glfw glfw)

target_link_libraries(scrap glfw)




