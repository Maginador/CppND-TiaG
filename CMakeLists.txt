cmake_minimum_required(VERSION 3.10)

project(cpp-ting)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake/")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_DIRS})
include_directories(${SDL2_TTF_DIRS})

file(GLOB project_SRCS src/*.cpp) #src/*.h

add_executable(cpp-ting ${project_SRCS})
target_link_libraries(cpp-ting ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})