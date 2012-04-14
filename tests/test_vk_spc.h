#ifndef VALKYRIE_TEST_VK_ROD_H_INCLUDED
#define VALKYRIE_TEST_VK_ROD_H_INCLUDED

#include "gtest/gtest.h"
#include "node.h"
#include "spc.h"
#include <boost/shared_ptr.hpp>

namespace
{

TEST (Spc, testSpcProps)
{
    using boost::shared_ptr;
    using valkyrie::Node;
    using valkyrie::Spc;

    shared_ptr<Node> n1 = valkyrie::make_shared(new Node(1, 0, 0));
    Spc spc(1, "some name", kTranslateYDof | kTranslateZDof, n1);
    ASSERT_EQ(spc.is_constrained_at(kTranslateYDof), true) << "Dof Y not reported as constrained!";
    ASSERT_EQ(spc.is_constrained_at(kTranslateZDof), true) << "Dof Z not reported as constrained!";
    ASSERT_EQ(spc.is_constrained_at(kTranslateXDof), false)<< "Dof X reported as constrained!";
    ASSERT_EQ(spc.is_constrained_at(kTranslateYDof | kTranslateZDof), true);
    ASSERT_EQ(spc.get_node(), n1);
}

}//~ ns:

#endif
