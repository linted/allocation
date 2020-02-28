include(ExternalProject)
include(ProcessorCount)

ProcessorCount(PROCESSOR_COUNT)
if(PROCESSOR_COUNT EQUAL 0)
    set(PROCESSOR_COUNT 1) 
endif()

set(INSTALL_GTEST Off CACHE BOOL "turn gtest install off")

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
    URL_HASH SHA256=f353606f24a579597a1ff5b51009a45d75da047b3975d82c3f613f85bcf312db
    CONFIGURE_COMMAND cmake -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/ptmalloc ${CMAKE_CURRENT_BINARY_DIR}/ptmalloc
    BUILD_COMMAND make linux-shared -j ${PROCESSOR_COUNT}
    INSTALL_COMMAND cmake -E copy ${CMAKE_CURRENT_BINARY_DIR}/ptmalloc/libptmalloc3.so ${CMAKE_BINARY_DIR}/bin
)

# build tcmalloc

ExternalProject_Add(
    tcmalloc 
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gperftools
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/gperftools
    BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/gperftools
    DOWNLOAD_COMMAND cmake -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/gperftools ${CMAKE_CURRENT_BINARY_DIR}/gperftools
    CONFIGURE_COMMAND pwd && ./autogen.sh --prefix=${CMAKE_CURRENT_BINARY_DIR} && ./configure
    BUILD_COMMAND make -j ${PROCESSOR_COUNT}
    INSTALL_COMMAND cmake -E copy ${CMAKE_CURRENT_BINARY_DIR}/gperftools/.libs/libtcmalloc.so ${CMAKE_CURRENT_BINARY_DIR}/gperftools/.libs/libtcmalloc_minimal.so ${CMAKE_BINARY_DIR}/bin
)

# build hoard

ExternalProject_Add(
    hoard
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/hoard
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/hoard
    BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/hoard/src
    DOWNLOAD_COMMAND cmake -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/hoard ${CMAKE_CURRENT_BINARY_DIR}/hoard
    CONFIGURE_COMMAND ""
    BUILD_COMMAND make CXX=${CMAKE_CXX_COMPILER} -j ${PROCESSOR_COUNT}
    INSTALL_COMMAND cmake -E copy ${CMAKE_CURRENT_BINARY_DIR}/hoard/src/libhoard.so ${CMAKE_BINARY_DIR}/bin
)

add_library(dlmalloc SHARED dlmalloc/source/dlmalloc.c)
# add_custom_command()

add_library(dlmalloc_threadsafe SHARED dlmalloc/source/dlmalloc.c)
target_compile_definitions(dlmalloc_threadsafe PUBLIC USE_LOCKS)
install(TARGETS dlmalloc_threadsafe dlmalloc DESTINATION ${CMAKE_BINARY_DIR}/bin)