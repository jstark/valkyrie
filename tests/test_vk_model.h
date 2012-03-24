#ifndef VALKYRIE_TEST_VK_MODEL_H_INCLUDED
#define VALKYRIE_TEST_VK_MODEL_H_INCLUDED

#include "gtest/gtest.h"
#include "entity.h"
#include "model.h"

namespace
{

TEST (Model, createNode)
{
    valkyrie::Model model(5, "a model");

    int flag = model.createNode(1, 0.0, 0.0);
    ASSERT_EQ(flag, kActionOK) << "could not create a node !";

    flag = model.createNode(2, 0.0, 0.0);
    ASSERT_EQ(flag, kActionOK) << "could not create a node !";

    flag = model.createNode(2, 1.0, 2.0);
    ASSERT_EQ(flag, kActionFailed | kActionErrorIdAlreadyExists) << "created node with existing id !";
}

} //~ ns:

#endif // VALKYRIE_TEST_VK_MODEL_H_INCLUDED
