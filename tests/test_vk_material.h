#ifndef VALKYRIE_TEST_VK_MATERIAL_H_INCLUDED
#define VALKYRIE_TEST_VK_MATERIAL_H_INCLUDED

#include <gtest/gtest.h>
#include "material.h"

namespace
{

TEST (Material, testMatProps)
{
    valkyrie::Material m1(10, "steel");
    ASSERT_DOUBLE_EQ(m1.get_E(), 2.1e11);
    ASSERT_DOUBLE_EQ(m1.get_rho(), 7800.0);

    valkyrie::Material m2(20, "aluminium", 48.0, 99.0);
    ASSERT_DOUBLE_EQ(m2.get_E(), 48.0);
    ASSERT_DOUBLE_EQ(m2.get_rho(), 99.0);
}

}//~ ns:

#endif // VALKYRIE_TEST_VK_MATERIAL_H_INCLUDED
