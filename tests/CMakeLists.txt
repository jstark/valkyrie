include_directories (../src)

set (TEST_HEADERS
        test_vk_version.h)
set (TEST_SOURCES tests.cpp)

add_executable (exec_tests ${SOURCES} ${TEST_HEADERS} ${TEST_SOURCES})
target_link_libraries (exec_tests ${GTEST_BOTH_LIBRARIES})
add_test(AllTests exec_tests)
