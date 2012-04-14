#ifndef VALKYRIE_TEST_VK_PROPERTY_H_INCLUDED
#define VALKYRIE_TEST_VK_PROPERTY_H_INCLUDED

#include "gtest/gtest.h"
#include "material.h"
#include "property.h"
#include <boost/shared_ptr.hpp>

namespace
{

TEST (Property, testProps)
{
    using boost::shared_ptr;
    using valkyrie::Property;
    using valkyrie::Material;

    shared_ptr<Material> m = valkyrie::try_create_material(1, 2.1e11, 7800.0, "steel");
    valkyrie::Property p(10, "some prop", m, 0.1);
    ASSERT_EQ(p.get_material(), m);
    ASSERT_DOUBLE_EQ(p.get_A(), 0.1);
}

}//~ ns:

#endif /* VALKYRIE_TEST_VK_PROPERTY_H_INCLUDED */
