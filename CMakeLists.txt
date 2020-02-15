cmake_minimum_required (VERSION 3.5.1)
project(Allocation C CXX)

add_subdirectory(deps)
add_subdirectory(code)

if(NOT DEFINED NO_DOCS)
add_subdirectory(docs)
endif()
