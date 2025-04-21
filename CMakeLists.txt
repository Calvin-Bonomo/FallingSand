cmake_minimum_required(VERSION 3.5)
project(GPU_FALLING_SAND)
list(APPEND SOURCES src/App.cpp src/Buffer.cpp)

set(OpenGL_GL_PREFERENCE "GLVND")

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} OpenGL::OpenGL glfw3)
target_include_directories(${PROJECT_NAME} PRIVATE ${OPENGL_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS})