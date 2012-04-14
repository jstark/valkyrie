#ifndef VALKYRIE_TEST_VK_ROD_H_INCLUDED
#define VALKYRIE_TEST_VK_ROD_H_INCLUDED

#include "gtest/gtest.h"
#include "material.h"
#include "property.h"
#include "node.h"
#include "rod.h"
#include <boost/shared_ptr.hpp>

namespace
{

TEST (Rod, testRodProps)
{
    using boost::shared_ptr;
    using valkyrie::Property;
    using valkyrie::Material;
    using valkyrie::Node;
    using valkyrie::Rod;

    shared_ptr<Material> m = valkyrie::try_create_material(1, 2.1e11, 7800.0, "steel");
    shared_ptr<Property> p = valkyrie::try_create_property(10, m, 0.1, "some prop");

    shared_ptr<Node> n1 = valkyrie::make_shared(new Node(1, 0, 0));
    shared_ptr<Node> n2 = valkyrie::make_shared(new Node(2, 1, 1));

    Rod r(20, "", p, n1, n2);
    ASSERT_EQ(r.get_property(), p);
    ASSERT_EQ(r.get_node1(), n1);
    ASSERT_EQ(r.get_node2(), n2);
}

}//~ ns:

#endif /* VALKYRIE_TEST_VK_ROD_H_INCLUDED */
