
set(CXX_FLAGS -Wall -Wextra -O3 -s )

add_executable(light_usage_test ${CMAKE_CURRENT_LIST_DIR}/light.cpp ${CMAKE_CURRENT_SOURCE_DIR}/light.c)
target_link_libraries(light_usage_test benchmark::benchmark)
target_compile_options(light_usage_test PUBLIC ${CXX_FLAGS})
target_include_directories(light_usage_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


add_executable(sporatic_usage_test ${CMAKE_CURRENT_LIST_DIR}/sporadic.cpp)
target_link_libraries(sporatic_usage_test benchmark::benchmark)
target_compile_options(sporatic_usage_test PUBLIC ${CXX_FLAGS})

