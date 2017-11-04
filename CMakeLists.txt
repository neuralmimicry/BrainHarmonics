cmake_minimum_required(VERSION 3.8)
project(opengl)

set(CMAKE_CXX_STANDARD 11)

message(${PROJECT_SOURCE_DIR}/common)
include_directories(${PROJECT_SOURCE_DIR}/common)
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/src)

set(GLAD "${PROJECT_SOURCE_DIR}/src/glad.c" "${PROJECT_SOURCE_DIR}/include/glad/glad.h" "${PROJECT_SOURCE_DIR}/include/KHR/khrplatform.h")

FIND_PACKAGE(OpenGL REQUIRED)
FIND_PACKAGE(glfw3 REQUIRED)
FIND_PACKAGE(GLEW REQUIRED)


include_directories(${OPENGL_INCLUDE_DIRS})



add_executable(twod twod.cpp ${GLAD})

add_executable(wave wave.cpp ${GLAD})

add_executable(transition_text transition_text.cpp ${GLAD} common/shader.cpp common/shader.hpp)

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




