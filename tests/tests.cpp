#include "gtest/gtest.h"

// tests
#include "test_vk_version.h"

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
