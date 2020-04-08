cmake_minimum_required(VERSION 3.8)
project(opengl)

set(CMAKE_CXX_STANDARD 11)

message(${PROJECT_SOURCE_DIR}/common)
include_directories(${PROJECT_SOURCE_DIR}/common)
include_directories(${PROJECT_SOURCE_DIR}/loading_lib/include)
include_directories(${PROJECT_SOURCE_DIR}/loading_lib/src)
include_directories(${PROJECT_SOURCE_DIR}/glad/include)
include_directories(${PROJECT_SOURCE_DIR}/linmath)

# Set the new API for OpenGL
set (OpenGL_GL_PREFERENCE GLVND)
FIND_PACKAGE(OpenGL REQUIRED)
FIND_PACKAGE(glfw3 REQUIRED)
FIND_PACKAGE(GLEW REQUIRED)

add_subdirectory(glad/)

include_directories(${OPENGL_INCLUDE_DIRS})



add_executable(twod twod.cpp glad)

add_executable(wave wave.cpp ${GLAD})

add_executable(transition_text transition_text.cpp ${GLAD} common/shader.cpp common/shader.hpp)

add_executable(mainshader mainshader.cpp ${GLAD})

add_executable(triangles triangles.cpp ${GLAD})

add_executable(first_glfw first_glfw.cpp)

add_executable(scrap scrap.cpp ${GLAD})





target_link_libraries(twod PUBLIC glfw)
target_link_libraries(twod PUBLIC ${CMAKE_DL_LIBS})
target_link_libraries(twod PRIVATE glad)

target_link_libraries(wave PUBLIC glfw)
target_link_libraries(wave PUBLIC ${CMAKE_DL_LIBS})
target_link_libraries(wave PRIVATE glad)

target_link_libraries(transition_text PUBLIC glfw)
target_link_libraries(transition_text PUBLIC ${CMAKE_DL_LIBS})
target_link_libraries(transition_text PRIVATE glad)

target_link_libraries(mainshader PUBLIC glfw)
target_link_libraries(mainshader PUBLIC ${CMAKE_DL_LIBS})
target_link_libraries(mainshader PRIVATE glad)

target_link_libraries(triangles PUBLIC glfw)
target_link_libraries(triangles PUBLIC ${CMAKE_DL_LIBS})
target_link_libraries(triangles PRIVATE glad)

target_link_libraries(first_glfw PUBLIC glfw)
target_link_libraries(first_glfw PUBLIC ${CMAKE_DL_LIBS})
target_link_libraries(first_glfw PRIVATE glad)

target_link_libraries(scrap glfw)




