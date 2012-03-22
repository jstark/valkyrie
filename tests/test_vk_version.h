#ifndef VALKYRIE_TEST_VK_VERSION_H_INCLUDED
#define VALKYRIE_TEST_VK_VERSION_H_INCLUDED

#include "gtest/gtest.h"
#include "version.h"

namespace
{

TEST (Version, testMajorVersion)
{
    ASSERT_EQ(valkyrie::Version::getMajor(), VK_API_MAJOR) << "error in getting major version !";
}

TEST (Version, testMinorVersion)
{
    ASSERT_EQ(valkyrie::Version::getMinor(), VK_API_MINOR) << "error in getting minor version !";
}

TEST (Version, testPatchVersion)
{
    ASSERT_EQ(valkyrie::Version::getPatch(), VK_API_PATCH) << "error in getting patch version !";
}

TEST (Version, testVersion)
{
    ASSERT_EQ(valkyrie::Version::getVersion(), VK_API_VERSION) << "error in getting api version !";
}

TEST (Version, testIsAtLeast)
{
    ASSERT_TRUE(valkyrie::Version::isAtLeast(VK_API_MAJOR, VK_API_MINOR, VK_API_PATCH)) << "error in querying version !";
}

} //~ ns:

#endif // VALKYRIE_TEST_VK_VERSION_H_INCLUDED
