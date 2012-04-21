#ifndef VALKYRIE_STATICANALYSIS_H_INCLUDED
#define VALKYRIE_STATICANALYSIS_H_INCLUDED

#include "valkyrie.h"
#include <boost/shared_ptr.hpp>

using boost::shared_ptr;

namespace valkyrie
{

class Model;

class DLL_HIDDEN StaticAnalysis
{
public:
    StaticAnalysis();

    int analyze(const Model& model);
};

}//~ ns:valkyrie

#endif // VALKYRIE_STATICANALYSIS_H_INCLUDED
