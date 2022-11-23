cmake_minimum_required(VERSION 3.23)
project(RQuaternion)

set(CMAKE_CXX_STANDARD 14)

include_directories(/usr/local/lib64/R/library/Rcpp/include/)
include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(RQuaternion RQuaternion.cpp)



