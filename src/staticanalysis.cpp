#include "staticanalysis.h"
#include "model.h"
#include "rod.h"
#include "node.h"
#include "property.h"
#include "material.h"
#include "force.h"
#include "spc.h"
#include <algorithm>
#include <boost/numeric/ublas/symmetric.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/vector.hpp>

using valkyrie::StaticAnalysis;
using valkyrie::Model;
using valkyrie::Rod;
using valkyrie::Node;
using valkyrie::Property;
using valkyrie::Material;
using valkyrie::Force;
using valkyrie::Spc;
using boost::numeric::ublas::matrix;
using boost::numeric::ublas::symmetric_matrix;
using boost::numeric::ublas::upper;
using boost::numeric::ublas::lu_factorize;
using boost::numeric::ublas::lu_substitute;
using boost::numeric::ublas::vector;
using boost::numeric::ublas::permutation_matrix;

#define MAX_ALLOWABLE_NODES     200
#define MAX_DOFS_PER_NODE         3
#define MAX_NODES_PER_ELEMENT     2

namespace
{
    struct updateStiffness
    {
        explicit updateStiffness(symmetric_matrix<double, upper> &K, std::map<int, int> *nid2row)
            : K_(K), nid2row_(nid2row) {}

        void operator()(const std::pair<int, shared_ptr<Rod> > &rod_entry) const
        {
            shared_ptr<Rod> rod = rod_entry.second;
            shared_ptr<Node> n1 = rod->get_node1();
            shared_ptr<Node> n2 = rod->get_node2();

            int indices[MAX_NODES_PER_ELEMENT * MAX_DOFS_PER_NODE] = {-1};

            // get rows/columns
            int id1 = n1->get_id();
            int row1= (*nid2row_)[id1];
            if (row1 == 0) // not added previously
            {
                (*nid2row_)[id1] = nid2row_->size()-1; // subtract 1 because it was added in the map by the [] operator
                row1 = nid2row_->size()-1;
            }

            int id2 = n2->get_id();
            int row2= (*nid2row_)[id2];
            if (row2 == 0)
            {
                (*nid2row_)[id2] = nid2row_->size()-1; // subtract 1 because it was added in the map by the [] operator
                row2 = nid2row_->size()-1;
            }

            indices[0] = (row1 + 0) * MAX_DOFS_PER_NODE;
            indices[1] = indices[0] + 1;
            indices[2] = indices[1] + 1;
            indices[3] = (row2 + 0) * MAX_DOFS_PER_NODE;
            indices[4] = indices[3] + 1;
            indices[5] = indices[4] + 1;

            double dx = n2->get_x() - n1->get_x();
            double dy = n2->get_y() - n1->get_y();
            double dz = n2->get_z() - n1->get_z();
            double eL = std::sqrt(dx*dx + dy*dy + dz*dz);
            double Cx = dx/eL;
            double Cy = dy/eL;
            double Cz = dz/eL;

            shared_ptr<Property> prop = rod->get_property();
            double A  = prop->get_A();

            shared_ptr<Material> matr = prop->get_material();
            double E  = matr->get_E();
            double ct = A*E/eL;

            // update stiffness
            K_(indices[0], indices[0]) += ct * Cx * Cx;
            K_(indices[0], indices[1]) += ct * Cx * Cy;
            K_(indices[0], indices[2]) += ct * Cx * Cz;
            K_(indices[0], indices[3]) -= ct * Cx * Cx;
            K_(indices[0], indices[4]) -= ct * Cx * Cy;
            K_(indices[0], indices[5]) -= ct * Cx * Cz;
            K_(indices[1], indices[1]) += ct * Cy * Cy;
            K_(indices[1], indices[2]) += ct * Cy * Cz;
            K_(indices[1], indices[3]) -= ct * Cx * Cy;
            K_(indices[1], indices[4]) -= ct * Cy * Cy;
            K_(indices[1], indices[5]) -= ct * Cy * Cz;
            K_(indices[2], indices[2]) += ct * Cz * Cz;
            K_(indices[2], indices[3]) -= ct * Cx * Cz;
            K_(indices[2], indices[4]) -= ct * Cy * Cz;
            K_(indices[2], indices[5]) -= ct * Cz * Cz;
            K_(indices[3], indices[3]) += ct * Cx * Cx;
            K_(indices[3], indices[4]) += ct * Cx * Cy;
            K_(indices[3], indices[5]) += ct * Cx * Cz;
            K_(indices[4], indices[4]) += ct * Cy * Cy;
            K_(indices[4], indices[5]) += ct * Cy * Cz;
            K_(indices[5], indices[5]) += ct * Cz * Cz;

        }

        symmetric_matrix<double, upper> &K_;
        std::map<int, int> *nid2row_;
    };

    struct updateLoads
    {
        updateLoads(vector<double> &F, std::map<int, int> *nid2row)
            : F_(F), nid2row_(nid2row)
        {

        }

        void operator()(const std::pair<int, shared_ptr<Force> > &force_entry) const
        {
            shared_ptr<Force> f = force_entry.second;
            shared_ptr<Node > n = f->get_node();

            int nid = n->get_id();
            int row_id = (*nid2row_)[nid];
            row_id *= MAX_DOFS_PER_NODE;
            F_(row_id + 0) = f->magnitude() * f->nx();
            F_(row_id + 1) = f->magnitude() * f->ny();
            F_(row_id + 2) = f->magnitude() * f->nz();
        }

        vector<double> &F_;
        std::map<int, int> *nid2row_;
    };

    struct applySpcs
    {
        applySpcs(symmetric_matrix<double, upper>& K, vector<double> &F, std::map<int, int> *nid2row)
            : K_(K), F_(F), nid2row_(nid2row) {}

        void operator()(const std::pair<int, shared_ptr<Spc> > spc_entry)
        {
            shared_ptr<Spc> spc = spc_entry.second;
            shared_ptr<Node> node = spc->get_node();

            int row_id = (*nid2row_)[node->get_id()];
            row_id *= MAX_DOFS_PER_NODE;

            int dim = K_.size1();
            for (int i = 0; i < dim; ++i)
            {
                if (spc->is_constrained_at(kTranslateXDof))
                {
                    K_(row_id + 0, i) = 0.0;
                    K_(i, row_id + 0) = 0.0;
                    F_(row_id + 0) = 0.0;
                }

                if (spc->is_constrained_at(kTranslateYDof))
                {
                    K_(row_id + 1, i) = 0.0;
                    K_(i, row_id + 1) = 0.0;
                    F_(row_id + 1) = 0.0;
                 }

                if (spc->is_constrained_at(kTranslateZDof))
                {
                    K_(row_id + 2, i) = 0.0;
                    K_(i, row_id + 2) = 0.0;
                    F_(row_id + 2) = 0.0;
                }
            }
            K_(row_id + 0, row_id + 0) = spc->is_constrained_at(kTranslateXDof) ? 1.0 : K_(row_id + 0, row_id + 0);
            K_(row_id + 1, row_id + 1) = spc->is_constrained_at(kTranslateYDof) ? 1.0 : K_(row_id + 1, row_id + 1);
            K_(row_id + 2, row_id + 2) = spc->is_constrained_at(kTranslateZDof) ? 1.0 : K_(row_id + 2, row_id + 2);
        }

        symmetric_matrix<double, upper> &K_;
        vector<double> F_;
        std::map<int, int> *nid2row_;
    };
}

StaticAnalysis::StaticAnalysis()
{
}

int StaticAnalysis::analyze(const Model& model)
{
    size_t numberOfNodes = model.nodes_num();

    if (numberOfNodes > MAX_ALLOWABLE_NODES * MAX_DOFS_PER_NODE)
    {
        return -1;
    }

    int n = numberOfNodes;

    // node ids might not be continuous, so we
    // do a mapping from node-id to row_id
    std::map<int, int> nid2row; // node_id : row_id

    // stiffness matrix
    symmetric_matrix<double, upper> K(n * MAX_DOFS_PER_NODE, n * MAX_DOFS_PER_NODE); // TODO: sparse matrix
    std::for_each(model.beginElems(), model.endElems(), updateStiffness(K, &nid2row));

    // force vector
    vector<double> F(n * MAX_DOFS_PER_NODE);
    std::for_each(model.beginForces(), model.endForces(), updateLoads(F, &nid2row));

    // apply spcs
    std::for_each(model.beginSpcs(), model.endSpcs(), applySpcs(K, F, &nid2row));

    // fix zero on diagonal
    // search for zero values on main diagonal of 'K'. if a zero is found, it is replaced
    // by a '1', and  the corresponding F element is set to 0 as well.
    for (int i = 0; i < n * MAX_DOFS_PER_NODE; ++i)
    {
        if (K(i,i) == 0.0)
        {
            K(i,i) = 1.0;
            F(i) = 0.0;
        }
    }

    // solution phase
    permutation_matrix<int> P(n * MAX_DOFS_PER_NODE);
    matrix<double> KK(K);
    lu_factorize(KK, P);

    vector<double> x(F);
    lu_substitute(KK, P, x);

    return 0;
}

#undef MAX_ALLOWABLE_NODES
#undef MAX_DOFS_PER_NODE
#undef MAX_NODES_PER_ELEMENT

