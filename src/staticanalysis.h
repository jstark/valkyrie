#ifndef VALKYRIE_STATICANALYSIS_H_INCLUDED
#define VALKYRIE_STATICANALYSIS_H_INCLUDED

#include "valkyrie.h"
#include <map>
#include "Eigen/Dense"

using Eigen::VectorXd;

namespace valkyrie
{



class Model;

struct NodalResults
{
    NodalResults()
        : ux(0), uy(0), uz(0), reactionX(0), reactionY(0), reactionZ(0) {}
    double ux, uy, uz;
    double reactionX, reactionY, reactionZ;
};

struct ElementalResults
{
public:
    ElementalResults()
        : stress(0), strain(0), force(0) {}

    double stress, strain, force;
};

class DLL_HIDDEN StaticAnalysisResults
{
public:
    typedef std::map<int, NodalResults> NodalResultsContainer;
    typedef std::map<int, ElementalResults> ElementalResultsContainer;
    typedef std::pair<int, NodalResults> nodal_result_item;
    typedef std::pair<int, ElementalResults> element_result_item;

    void setNodalResult(int nid, double ux, double uy, double uz, double rx, double ry, double rz);
    const NodalResults& nodalResults(int nid) { return nodalResults_[nid]; }
    void setElementalResult(int eid, double strain, double stress, double force);
    const ElementalResults& elementalResults(int eid) { return elementalResults_[eid]; }

    typedef NodalResultsContainer::const_iterator nodal_result_const_iterator;
    typedef ElementalResultsContainer::const_iterator element_result_const_iterator;

    nodal_result_const_iterator beginNodalResults() const { return nodalResults_.begin(); }
    nodal_result_const_iterator endNodalResults() const { return nodalResults_.end(); }

    element_result_const_iterator beginElementResults() const { return elementalResults_.begin(); }
    element_result_const_iterator endElementResults() const { return elementalResults_.end(); }
private:
    NodalResultsContainer nodalResults_;
    ElementalResultsContainer elementalResults_;
};

class DLL_HIDDEN StaticAnalysis
{
public:
    StaticAnalysis();

    int analyze(const Model& model, StaticAnalysisResults &results);
};

}//~ ns:valkyrie

#endif // VALKYRIE_STATICANALYSIS_H_INCLUDED
