
set(CXX_FLAGS -Wall -Wextra -O3 -s -static )

add_executable(light_usage_test ${CMAKE_CURRENT_LIST_DIR}/light.cpp ${CMAKE_CURRENT_SOURCE_DIR}/light.c)
target_link_libraries(light_usage_test PRIVATE benchmark::benchmark)
target_compile_options(light_usage_test PUBLIC ${CXX_FLAGS})
target_include_directories(light_usage_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(light_usage_test_threaded ${CMAKE_CURRENT_LIST_DIR}/light.cpp ${CMAKE_CURRENT_SOURCE_DIR}/light.c)
target_link_libraries(light_usage_test_threaded PRIVATE benchmark::benchmark)
target_compile_options(light_usage_test_threaded PUBLIC ${CXX_FLAGS})
target_compile_definitions(light_usage_test_threaded PRIVATE DO_THREADED_TESTS=1)
target_include_directories(light_usage_test_threaded PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


add_executable(sporatic_usage_test ${CMAKE_CURRENT_LIST_DIR}/sporadic.cpp ${CMAKE_CURRENT_LIST_DIR}/sporadic.c)
target_link_libraries(sporatic_usage_test PRIVATE benchmark::benchmark)
target_compile_options(sporatic_usage_test PUBLIC ${CXX_FLAGS})
target_include_directories(sporatic_usage_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(sporatic_usage_test_threaded ${CMAKE_CURRENT_LIST_DIR}/sporadic.cpp ${CMAKE_CURRENT_LIST_DIR}/sporadic.c)
target_link_libraries(sporatic_usage_test_threaded PRIVATE benchmark::benchmark)
target_compile_options(sporatic_usage_test_threaded PUBLIC ${CXX_FLAGS})
target_compile_definitions(sporatic_usage_test_threaded PRIVATE DO_THREADED_TESTS=1)
target_include_directories(sporatic_usage_test_threaded PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS sporatic_usage_test sporatic_usage_test_threaded light_usage_test light_usage_test_threaded DESTINATION ${CMAKE_BINARY_DIR}/bin/)
install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/graph.py ${CMAKE_CURRENT_SOURCE_DIR}/run_tests.sh DESTINATION ${CMAKE_BINARY_DIR}/bin/)