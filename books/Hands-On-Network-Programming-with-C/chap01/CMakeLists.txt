cmake_minimum_required(VERSION 3.15)

project(net)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wfatal-errors")

include_directories()

file(GLOB SRC_FILES ./win_list.c)

set(OBJ_NAME net)

add_executable(${OBJ_NAME} ${SRC_FILES})

target_link_libraries(${OBJ_NAME} iphlpapi ws2_32)

#iphlpapi