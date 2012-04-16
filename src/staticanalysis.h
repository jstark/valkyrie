#ifndef VALKYRIE_STATICANALYSIS_H_INCLUDED
#define VALKYRIE_STATICANALYSIS_H_INCLUDED

#include "valkyrie.h"
#include "model.h"
#include <boost/shared_ptr.hpp>

namespace valkyrie
{

struct NodeDispl
{
    double x, y, z;
};

struct RodStress
{
    double stress;
};

struct RodStrain
{
    double strain;
};

class DLL_HIDDEN StaticAnalysis
{
public:
    StaticAnalysis();

    void analyze(shared_ptr<Model> model);
private:

};

}//~ ns:valkyrie

#endif // VALKYRIE_STATICANALYSIS_H_INCLUDED
