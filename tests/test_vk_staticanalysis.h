#ifndef VALKYRIE_TEST_VK_STATICANALYSIS_H
#define VALKYRIE_TEST_VK_STATICANALYSIS_H

#include "gtest/gtest.h"
#include "model.h"
#include "staticanalysis.h"

namespace
{

TEST (StaticAnalysis, testStiffness)
{
    using namespace valkyrie;

    Model m(1, "6-bar truss");

    double E = 1.9e06;
    double A = 8.0;

    m.createMaterial(1, E);
    m.createProperty(1, 1, A);

    m.createNode(1,  0,  0, 0);
    m.createNode(2, 36,  0, 0);
    m.createNode(3,  0, 36, 0);
    m.createNode(4, 36, 36, 0);
    m.createNode(5, 72, 36, 0);

    m.createRod(1, 1, 1, 2);
    m.createRod(2, 1, 2, 3);
    m.createRod(3, 1, 3, 4);
    m.createRod(4, 1, 2, 4);
    m.createRod(5, 1, 2, 5);
    m.createRod(6, 1, 4, 5);

    m.createSpc(1, kTranslateXDof | kTranslateYDof | kTranslateZDof, 1);
    m.createSpc(2, kTranslateXDof | kTranslateYDof | kTranslateZDof, 3);

    m.createForce(1, 4, 500, 0, -1, 0);
    m.createForce(2, 5, 500, 0, -1, 0);

    StaticAnalysis analysis;
    StaticAnalysisResults results;
    analysis.analyze(m, results);

    printf("%8s\t%8s\t%8s\t%8s\t%8s\t%8s\t%8s\n", "Node ID", "UX", "UY", "UZ", "React X", "React Y", "React Z");
    for (int i = 1; i < 6; ++i)
    {
        NodalResults nodal = results.nodalResults(i);
        printf("% 8d\t% 8.3le\t% 8.3le\t% 8.3le\t% 8.3le\t% 8.3le\t% 8.3le\n",
               i, nodal.ux, nodal.uy, nodal.uz, nodal.reactionX, nodal.reactionY, nodal.reactionZ);
    }

    printf("%8s\t%8s\t%8s\t%8s\n", "Elem ID", "Strain", "Stress", "Force");
    for (int i = 1; i < 7; ++i)
    {
        ElementalResults elem = results.elementalResults(i);
        printf("% 8d\t% 8.3le\t% 8.3le\t% 8.3le\n", i, elem.strain, elem.stress, elem.force);
    }
}

}

#endif // VALKYRIE_TEST_VK_STATICANALYSIS_H
