include_directories (../src)

set (TEST_HEADERS
        test_vk_version.h
        test_vk_entity.h
        test_vk_model.h
        test_vk_node.h
        test_vk_force.h
        test_vk_material.h
        test_vk_property.h
        test_vk_spc.h
        test_vk_rod.h
        test_vk_staticanalysis.h)
set (TEST_SOURCES tests.cpp)

add_executable (exec_tests ${SOURCES} ${TEST_HEADERS} ${TEST_SOURCES})
target_link_libraries (exec_tests ${GTEST_BOTH_LIBRARIES})
add_test(AllTests exec_tests)
