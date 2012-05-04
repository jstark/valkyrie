#include "valkyrie.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    printf("Valkyrie Version = %s\n", VKApiVersion());

    VKModelCreate(1, "single-bar");
    VKModelCreateMaterial(1, 1, 2.1e11, 7800.0, "steel");
    VKModelCreateProperty(1, 1, 1, 0.1, "steel property");
    VKModelCreateNode(1, 1, 0.0, 0.0, 0.0);
    VKModelCreateNode(1, 2, 1.0, 0.0, 0.0);
    VKModelCreateRod(1, 1, 1, 1, 2);
    VKModelCreateSpc(1, 1, VKDofCode(1, 1, 0), 1);
    VKModelCreateSpc(1, 2, VKDofCode(0, 1, 0), 2);
    VKModelCreateForce(1, 1, 2, 51.0, 1, 0, 0);

    int analysis_code = VKModelPerformStaticAnalysis(1);
    printf("Analysis message: %s\n", VKErrorMessage(analysis_code));
    VKStaticAnalysisPrintResults(1);
    return 0;
}
