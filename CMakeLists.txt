# Authors: Luca Tagliapietra, Elena Ceseracciu, and Monica Reggiani

cmake_minimum_required(VERSION 2.6)

# Define project
project (MBSBenchmarks)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# find dependencies (Opensim)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
find_package(OpenSim REQUIRED)

add_subdirectory(lib)
add_subdirectory(src)


file(COPY data DESTINATION ${CMAKE_BINARY_DIR})
