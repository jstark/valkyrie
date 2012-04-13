#ifndef VALKYRIE_TEST_VK_FORCE_H_INCLUDED
#define VALKYRIE_TEST_VK_FORCE_H_INCLUDED

#include "gtest/gtest.h"
#include "force.h"
#include "node.h"
#include <boost/shared_ptr.hpp>

using  boost::shared_ptr;

namespace
{

using valkyrie::Node;
using valkyrie::Force;

TEST (Force, testProperties)
{
    shared_ptr<Node> n = valkyrie::make_shared(new Node(1, 0, 0));
    Force f(10, "", n, 10.2, 0.0, 1.0, 0.0);
    ASSERT_EQ(n, f.node());
    ASSERT_DOUBLE_EQ(f.magnitude(), 10.2);
    ASSERT_DOUBLE_EQ(f.nx(), 0.0);
    ASSERT_DOUBLE_EQ(f.ny(), 1.0);
    ASSERT_DOUBLE_EQ(f.nz(), 0.0);
}

}

#endif // VALKYRIE_TEST_VK_FORCE_H_INCLUDED
