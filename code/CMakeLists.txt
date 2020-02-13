
set(CXX_FLAGS -Wall -Wextra -O3 -s )

add_executable(light_usage_test ${CMAKE_CURRENT_LIST_DIR}/light.cpp)
target_link_libraries(light_usage_test benchmark::benchmark)
target_compile_options(light_usage_test PUBLIC ${CXX_FLAGS})


add_executable(sporatic_usage_test ${CMAKE_CURRENT_LIST_DIR}/sporadic.cpp)
target_link_libraries(sporatic_usage_test benchmark::benchmark)
target_compile_options(sporatic_usage_test PUBLIC ${CXX_FLAGS})

