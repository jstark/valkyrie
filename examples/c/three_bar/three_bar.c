#include "valkyrie.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    printf("Valkyrie Version = %s\n", VKApiVersion());

    VKModelCreate(1, "three-bar");
    VKModelCreateMaterial(1, 1, 30e6, 7800.0, "");
    VKModelCreateProperty(1, 1, 1, 2, "");
    VKModelCreateNode(1, 1, 0.0, 0.0, 0.0);
    VKModelCreateNode(1, 2, 10.0, 0.0, 0.0);
    VKModelCreateNode(1, 3, 10.0, 10.0, 0.0);
    VKModelCreateNode(1, 4, 0.0, 10.0, 0.0);
    VKModelCreateRod(1, 1, 1, 1, 2);
    VKModelCreateRod(1, 2, 1, 1, 3);
    VKModelCreateRod(1, 3, 1, 1, 4);
    VKModelCreateSpc(1, 1, VKDofCode(1, 1, 0), 2);
    VKModelCreateSpc(1, 2, VKDofCode(1, 1, 0), 3);
    VKModelCreateSpc(1, 3, VKDofCode(1, 1, 0), 4);
    VKModelCreateForce(1, 1, 1, 10000, 0, -1, 0);

    int analysis_code = VKModelPerformStaticAnalysis(1);
    printf("Analysis message: %s\n", VKErrorMessage(analysis_code));
    VKStaticAnalysisPrintResults(1);
    return 0;
}
