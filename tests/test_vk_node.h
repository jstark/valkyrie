#ifndef VALKYRIE_TEST_VK_NODE_H_INCLUDED
#define VALKYRIE_TEST_VK_NODE_H_INCLUDED

#include "gtest/gtest.h"
#include "node.h"

namespace
{

TEST (Node, testXYZ)
{
    valkyrie::Node n(10, -5.3, 9.000, 4.56);
    ASSERT_DOUBLE_EQ(n.get_x(), -5.3);
    ASSERT_DOUBLE_EQ(n.get_y(), 9.000);
    ASSERT_DOUBLE_EQ(n.get_z(), 4.56);
}

}//~ ns

#endif // VALKYRIE_TEST_VK_NODE_H_INCLUDED
