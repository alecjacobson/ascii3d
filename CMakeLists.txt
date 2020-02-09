cmake_minimum_required(VERSION 3.1)
project(ascii3d)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# libigl
#option(LIBIGL_USE_STATIC_LIBRARY     "Use Static Library" ON)
option(LIBIGL_WITH_EMBREE             "Use Embree"         ON)

find_package(LIBIGL REQUIRED QUIET)

add_library(ascii ascii_art.cpp)
target_link_libraries(ascii)

add_executable(image2ascii image2ascii.cpp)
target_link_libraries(image2ascii ascii)

add_executable(spy spy.cpp)
target_link_libraries(spy ascii igl::core)

file(GLOB SRC_CPP src/*.cpp)
add_executable(ascii3d ascii3d.cpp ${SRC_CPP})
target_include_directories(ascii3d PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(ascii3d ascii igl::core igl::embree)
