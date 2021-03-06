#include "gtest/gtest.h"

// tests
#include "test_vk_version.h"
#include "test_vk_entity.h"
#include "test_vk_model.h"
#include "test_vk_node.h"
#include "test_vk_force.h"
#include "test_vk_material.h"
#include "test_vk_property.h"
#include "test_vk_spc.h"
#include "test_vk_rod.h"
#include "test_vk_staticanalysis.h"

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
