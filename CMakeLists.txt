cmake_minimum_required(VERSION 3.5)
project(GPU_FALLING_SAND)
set(CXX_STANDARD 14)
list(APPEND SOURCES src/App.cpp src/Buffer.cpp src/TextureBuffer.cpp src/ComputeProgram.cpp src/FallingSand.cpp 
  src/GLFWContext.cpp src/Shader.cpp src/ShaderProgram.cpp src/VertexArrayObject.cpp)
list(APPEND HEADERS src/Buffer.hpp src/ComputeProgram.hpp src/FallingSand.hpp
  src/GLFWContext.hpp src/Shader.hpp src/ShaderProgram.hpp src/TextureBuffer.hpp
  src/VertexArrayObject.hpp)

set(OpenGL_GL_PREFERENCE "GLVND")

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} OpenGL::OpenGL glfw)
target_include_directories(${PROJECT_NAME} PRIVATE ${OPENGL_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS})