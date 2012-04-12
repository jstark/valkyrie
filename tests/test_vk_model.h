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

TEST (Model, createRod)
{
    valkyrie::Model model(5, "a model");

    model.createMaterial(2); // id = 2
    model.createProperty(1, 2, 0.1, "steel");
    model.createNode(1, 0, 0);
    model.createNode(2, 1, 1);
    int flag = model.createRod(1, 1, 1, 2);
    ASSERT_EQ(flag, kActionOK) << "could not create a rod element !";
}

TEST (Model, createInvalidRod)
{
    valkyrie::Model model(5, "a model");

    int flag = model.createRod(1, 1, 1, 2);
    ASSERT_EQ(flag, kActionFailed | kActionErrorInvalidArgs) << "Allowed to create rod with invalid property !";

    model.createMaterial(2);
    model.createProperty(1, 2, 0.1, "some property");
    flag = model.createRod(1, 1, 17, 0);
    ASSERT_EQ(flag, kActionFailed | kActionErrorInvalidArgs) << "Allowed to create rod with invalid node !";

    model.createNode(1, 0, 0);
    flag = model.createRod(1, 1, 1, 35);
    ASSERT_EQ(flag, kActionFailed | kActionErrorInvalidArgs) << "Allowed to create rod with invalid node !";
    flag = model.createRod(1, 1, 1, 1 );
    ASSERT_EQ(flag, kActionFailed | kActionErrorInvalidArgs) << "Allowed to create rod on duplicate node !";

    model.createNode(2, 1, 1);
    flag = model.createRod(1, 1, 1, 2);
    ASSERT_EQ(flag, kActionOK) << "could not create a rod element !";

    flag = model.createRod(1, 1, 1, 2);
    ASSERT_EQ(flag, kActionFailed | kActionErrorIdAlreadyExists) << "Allowed to create rod with duplicate id !";

}

TEST (Model, createSpc)
{
    valkyrie::Model model(5, "a model");

    model.createNode(1, 0, 0);
    int flag = model.createSpc(1, 123, 1);
    ASSERT_EQ(flag, kActionOK) << "could not create a Spc constraint !";

    flag = model.createSpc(1, 123, 1);
    ASSERT_EQ(flag, kActionFailed | kActionErrorIdAlreadyExists) << "Allowed to create Spc with duplicate id !";
}

TEST (Model, createInvalidSpc)
{
    valkyrie::Model model(5, "a model");

    int flag = model.createSpc(1, 123, 57);
    ASSERT_EQ(flag, kActionFailed | kActionErrorInvalidArgs) << "Allowed to create rod with invalid node !";
}

} //~ ns:

#endif // VALKYRIE_TEST_VK_MODEL_H_INCLUDED
