include(ExternalProject)
include(ProcessorCount)

ProcessorCount(PROCESSOR_COUNT)
if(PROCESSOR_COUNT EQUAL 0)
    set(PROCESSOR_COUNT 1) 
endif()

add_subdirectory(googletest EXCLUDE_FROM_ALL)
add_subdirectory(benchmark EXCLUDE_FROM_ALL)


# build jemalloc


ExternalProject_Add(
    jemalloc 
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/jemalloc
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/jemalloc
    BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/jemalloc
    DOWNLOAD_COMMAND cmake -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/jemalloc ${CMAKE_CURRENT_BINARY_DIR}/jemalloc
    CONFIGURE_COMMAND pwd && ./autogen.sh --prefix=${CMAKE_CURRENT_BINARY_DIR}
    BUILD_COMMAND make -j ${PROCESSOR_COUNT}
    INSTALL_COMMAND cmake -E copy ${CMAKE_CURRENT_BINARY_DIR}/jemalloc/lib/libjemalloc.so.2 ${CMAKE_BINARY_DIR}/bin
)

# build ptmalloc

ExternalProject_Add(
    ptmalloc
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/ptmalloc
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ptmalloc
    BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/ptmalloc
    URL http://www.malloc.de/malloc/ptmalloc3-current.tar.gz
    CONFIGURE_COMMAND cmake -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/ptmalloc ${CMAKE_CURRENT_BINARY_DIR}/ptmalloc
    BUILD_COMMAND make linux-shared -j ${PROCESSOR_COUNT}
    INSTALL_COMMAND cmake -E copy ${CMAKE_CURRENT_BINARY_DIR}/ptmalloc/libptmalloc3.so ${CMAKE_BINARY_DIR}/bin
)