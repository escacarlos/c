cmake_minimum_required(VERSION 3.10)
project(OpenGL_Cylinder C)

set(CMAKE_C_STANDARD 11)

# Define source files
set(SOURCES main.c)

# Option to select GLAD or GLEW
option(USE_GLAD "Use GLAD instead of GLEW" ON)

if(USE_GLAD)
    message(STATUS "Using GLAD")
    set(SOURCES ${SOURCES} glad.c)
else()
    message(STATUS "Using GLEW")
    find_package(GLEW REQUIRED)
endif()

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(cylinder ${SOURCES})

if(USE_GLAD)
    target_include_directories(cylinder PRIVATE ${CMAKE_SOURCE_DIR}/glad)
else()
    target_link_libraries(cylinder GLEW::GLEW)
endif()

target_link_libraries(cylinder glfw OpenGL::GL m)

#mkdir build && cd build
#cmake .. -DUSE_GLAD=ON
#cmake .. -DUSE_GLAD=OFF
#cmake --build .
#./cylinder
