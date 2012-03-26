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

TEST (Model, createMaterial)
{
    valkyrie::Model model(5, "a model");
    int flag = model.createMaterial(1);
    ASSERT_EQ(flag, kActionOK) << "could not create a material !";

    flag = model.createMaterial(2);
    ASSERT_EQ(flag, kActionOK) << "could not create a material !";

    flag = model.createMaterial(2);
    ASSERT_EQ(flag, kActionFailed | kActionErrorIdAlreadyExists) << "Two (or more) materials have the same id !";
}

TEST (Model, createInvalidMaterial)
{
    valkyrie::Model model(5, "a model");
    int flag = model.createMaterial(1, -4);
    ASSERT_EQ(flag, kActionFailed | kActionErrorInvalidArgs) << "Allowed to create material with E = -4 !";

    flag = model.createMaterial(1, 2.1e11, 0);
    ASSERT_EQ(flag, kActionFailed | kActionErrorInvalidArgs) << "Allowed to create material with rho = 0 !";
}

TEST (Model, createProperty)
{
    valkyrie::Model model(5, "a model");
    model.createMaterial(5);
    int flag = model.createProperty(1, 5, 0.1);
    ASSERT_EQ(flag, kActionOK) << "could not create a property !";

    flag = model.createProperty(2, 5, 0.1);
    ASSERT_EQ(flag, kActionOK) << "could not create a property !";

    flag = model.createProperty(2, 5, 0.1);
    ASSERT_EQ(flag, kActionFailed | kActionErrorIdAlreadyExists) << "Two (or more) properties have the same id !";
}

TEST (Model, createInvalidProperty)
{
    valkyrie::Model model(5, "a model");

    int flag = model.createProperty(1, 2, 0.1, "steel");
    ASSERT_EQ(flag, kActionFailed | kActionErrorInvalidArgs) << "Allowed to create property with invalid material !";

    model.createMaterial(2);
    flag = model.createProperty(1, 2, -4.0);
    ASSERT_EQ(flag, kActionFailed | kActionErrorInvalidArgs) << "Allowed to create property with negative cross-section !";
}

} //~ ns:

#endif // VALKYRIE_TEST_VK_MODEL_H_INCLUDED
