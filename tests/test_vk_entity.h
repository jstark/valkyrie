#ifndef VALKYRIE_TEST_VK_ENTITY_H_INCLUDED
#define VALKYRIE_TEST_VK_ENTITY_H_INCLUDED

#include "gtest/gtest.h"
#include "entity.h"

namespace
{

TEST (Entity, testId)
{
    valkyrie::Entity entity(5);
    ASSERT_EQ(entity.get_id(), 5) << "error in getting the 'id' of an entity !";
}

TEST (Entity, testName)
{
    valkyrie::Entity entity1(5);
    ASSERT_EQ(entity1.get_name(), "") << "error in getting the 'name' of an entity !";

    valkyrie::Entity entity2(10, "truss");
    ASSERT_EQ(entity2.get_name(), "truss") << "error in getting the 'name' of an entity !";
}

} //~ ns:

#endif // VALKYRIE_TEST_VK_ENTITY_H_INCLUDED
