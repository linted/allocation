
add_executable(mal ${CMAKE_CURRENT_LIST_DIR}/mal.cpp)
target_link_libraries(mal benchmark::benchmark)

add_executable(mal_s ${CMAKE_CURRENT_LIST_DIR}/mal_s.cpp)
target_link_libraries(mal_s benchmark::benchmark)