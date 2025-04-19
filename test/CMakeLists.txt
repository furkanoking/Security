add_executable(test_main test.cpp)


target_include_directories(test_main PRIVATE /usr/src/gtest/include)
target_include_directories(test_main PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(test_main PRIVATE ${CMAKE_SOURCE_DIR}/include)


target_link_libraries(test_main SecurityLib)
target_link_libraries(test_main gtest gtest_main)