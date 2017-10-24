cmake_minimum_required(VERSION 3.8)
project(opengl)

set(DEPS "/home/user/opengl_dev/glfw-3.2.1/deps")
set(CMAKE_CXX_STANDARD 11)

include_directories(${DEPS})
message(${PROJECT_SOURCE_DIR}/common)
include_directories(${PROJECT_SOURCE_DIR}/common)


set(GLAD "${DEPS}/glad/glad.h" "${DEPS}/glad.c")

FIND_PACKAGE(OpenGL REQUIRED)
FIND_PACKAGE(glfw3 REQUIRED)
FIND_PACKAGE(GLEW REQUIRED)

add_library(glewstat STATIC ${GLEW_LIBRARIES})

include_directories(${OPENGL_INCLUDE_DIRS})

add_executable(first first_glfw.cpp ${GLAD})
add_executable(second twod.cpp ${GLAD})
add_executable(third triangles.cpp ${GLAD})
add_executable(wave wave.cpp ${GLAD})
add_executable(origwave waveback.c ${GLAD})
add_executable(shady mainshader.cpp ${GLAD} common/shader.cpp common/shader.hpp)

target_link_libraries(first glfw)
target_link_libraries(second glfw)
target_link_libraries(third glfw)
target_link_libraries(wave glfw)
target_link_libraries(origwave glfw)
## shady gets more libraries
target_link_libraries(shady glfw)
target_link_libraries(shady glewstat)
target_link_libraries(shady ${OPENGL_LIBRARIES})



