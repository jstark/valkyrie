#include "staticanalysis.h"
#include "model.h"
#include "rod.h"
#include "node.h"
#include "property.h"
#include "material.h"
#include "force.h"
#include "spc.h"
#include <algorithm>
#include <memory>

using valkyrie::StaticAnalysis;
using valkyrie::Model;
using valkyrie::Rod;
using valkyrie::Node;
using valkyrie::Property;
using valkyrie::Material;
using valkyrie::Force;
using valkyrie::Spc;
using valkyrie::StaticAnalysisResults;

#define MAX_ALLOWABLE_NODES     200
#define MAX_DOFS_PER_NODE         3
#define MAX_NODES_PER_ELEMENT     2
//#define D_PRINT_INITIAL_SYSTEM
//#define D_PRINT_FINAL_SYSTEM      
using Eigen::MatrixXd;
using Eigen::VectorXd;

namespace
{
    static void globalToLocal(double Cx, double Cy, double Cz, MatrixXd &T)
    {
        T(0, 0) = Cx; T(0, 1) = Cy; T(0, 2) = Cz; T(0, 3) = 0.; T(0, 4) = 0.; T(0, 5) = 0.;
        T(1, 0) = 0.; T(1, 1) = 0.; T(1, 2) = 0.; T(1, 3) = Cx; T(1, 4) = Cy; T(1, 5) = Cz;
    }

    static void transformationMatrix(double Cx, double Cy, double Cz, MatrixXd &T)
    {
        T(0, 0) = Cx * Cx; T(0, 1) = Cx * Cy; T(0, 2) = Cx * Cz; T(0, 3) = -Cx * Cx; T(0, 4) = -Cx * Cy; T(0, 5) = -Cx * Cz;
        T(1, 0) = Cx * Cy; T(1, 1) = Cy * Cy; T(1, 2) = Cy * Cz; T(1, 3) = -Cx * Cy; T(1, 4) = -Cy * Cy; T(1, 5) = -Cy * Cz;
        T(2, 0) = Cx * Cz; T(2, 1) = Cy * Cz; T(2, 2) = Cz * Cz; T(2, 3) = -Cx * Cz; T(2, 4) = -Cy * Cz; T(2, 5) = -Cz * Cz;
        T(3, 0) =-Cx * Cx; T(3, 1) =-Cx * Cy; T(3, 2) =-Cx * Cz; T(3, 3) =  Cx * Cx; T(3, 4) =  Cx * Cy; T(3, 5) =  Cx * Cz;
        T(4, 0) =-Cx * Cy; T(4, 1) =-Cy * Cy; T(4, 2) =-Cy * Cz; T(4, 3) =  Cx * Cy; T(4, 4) =  Cy * Cy; T(4, 5) =  Cy * Cz;
        T(5, 0) =-Cx * Cz; T(5, 1) =-Cy * Cz; T(5, 2) =-Cz * Cz; T(5, 3) =  Cx * Cz; T(5, 4) =  Cy * Cz; T(5, 5) =  Cz * Cz;
    }

    struct updateStiffness
    {
        explicit updateStiffness(MatrixXd &K, std::map<int, int> *nid2row)
            : K_(K), nid2row_(nid2row) {}

        void operator()(const std::pair<int, std::shared_ptr<Rod> > &rod_entry) const
        {
            std::shared_ptr<Rod> rod = rod_entry.second;
            std::shared_ptr<Node> n1 = rod->get_node1();
            std::shared_ptr<Node> n2 = rod->get_node2();

            int indices[MAX_NODES_PER_ELEMENT * MAX_DOFS_PER_NODE] = {-1};

            typedef std::map<int,int>::const_iterator const_iterator;

            // get rows/columns
            int id1 = n1->get_id();
            const_iterator iter = nid2row_->find(id1);
            int row1 = -1;
            if (iter == nid2row_->end()) // not added previously
            {
                row1 = nid2row_->size();
                (*nid2row_)[id1] = row1; 
            } else
            {
                row1 = iter->second;
            }

            int id2 = n2->get_id();
            iter = nid2row_->find(id2);
            int row2 = -1;
            if (iter == nid2row_->end())
            {
                row2 = nid2row_->size();
                (*nid2row_)[id2] = row2; 
            } else
            {
                row2 = iter->second;
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

            std::shared_ptr<Property> prop = rod->get_property();
            double A  = prop->get_A();

            std::shared_ptr<Material> matr = prop->get_material();
            double E  = matr->get_E();
            double ct = A*E/eL;

            MatrixXd T(MAX_DOFS_PER_NODE * MAX_NODES_PER_ELEMENT, MAX_DOFS_PER_NODE * MAX_NODES_PER_ELEMENT);
            transformationMatrix(Cx, Cy, Cz, T);
            for (int i = 0; i < MAX_DOFS_PER_NODE * MAX_NODES_PER_ELEMENT; ++i)
            {
                for (int j = 0; j < MAX_DOFS_PER_NODE * MAX_NODES_PER_ELEMENT; ++j)
                {
                    K_(indices[i], indices[j]) += ct * T(i, j);
                }
            }
        }

        MatrixXd &K_;
        std::map<int, int> *nid2row_;
    };

    struct updateLoads
    {
        updateLoads(VectorXd &F, std::map<int, int> *nid2row)
            : F_(F), nid2row_(nid2row)
        {

        }

        void operator()(const std::pair<int, std::shared_ptr<Force> > &force_entry) const
        {
            std::shared_ptr<Force> f = force_entry.second;
            std::shared_ptr<Node > n = f->get_node();

            int nid = n->get_id();
            int row_id = (*nid2row_)[nid];
            row_id *= MAX_DOFS_PER_NODE;
            F_(row_id + 0) = f->magnitude() * f->nx();
            F_(row_id + 1) = f->magnitude() * f->ny();
            F_(row_id + 2) = f->magnitude() * f->nz();
        }

        VectorXd &F_;
        std::map<int, int> *nid2row_;
    };

    struct applySpcs
    {
        applySpcs(MatrixXd& K, VectorXd &F, std::map<int, int> *nid2row)
            : K_(K), F_(F), nid2row_(nid2row) {}

        void operator()(const std::pair<int, std::shared_ptr<Spc> > spc_entry)
        {
            std::shared_ptr<Spc> spc = spc_entry.second;
            std::shared_ptr<Node> node = spc->get_node();

            int row_id = (*nid2row_)[node->get_id()];
            row_id *= MAX_DOFS_PER_NODE;

            int dim = K_.rows();
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

        MatrixXd &K_;
        VectorXd F_;
        std::map<int, int> *nid2row_;
    };

    struct updateNodalResults
    {
        updateNodalResults(const std::map<int, int> &nid2row, const VectorXd &x, const VectorXd &r, StaticAnalysisResults *results)
            : nid2row_(nid2row), x_(x), r_(r), results_(results) {}

        void operator()(const std::pair<int, std::shared_ptr<Node> > &node_entry)
        {
            int node_id = node_entry.first;

            int row = nid2row_[node_id];
            row *= MAX_DOFS_PER_NODE;
            results_->setNodalResult(node_id, x_(row + 0), x_(row + 1), x_(row + 2), r_(row + 0), r_(row + 1), r_(row + 2));
        }

        std::map<int, int> nid2row_;
        const VectorXd &x_;
        const VectorXd &r_;
        StaticAnalysisResults *results_;
    };

    struct updateElementalResults
    {
        updateElementalResults(StaticAnalysisResults *results)
            : results_(results) {}

        void operator()(const std::pair<int, std::shared_ptr<Rod> > &rod_entry)
        {
            int rod_id = rod_entry.first;
            std::shared_ptr<Rod> rod = rod_entry.second;
            std::shared_ptr<Node> n1 = rod->get_node1();
            std::shared_ptr<Node> n2 = rod->get_node2();

            int nid1 = n1->get_id();
            int nid2 = n2->get_id();
            const valkyrie::NodalResults res1 = results_->nodalResults(nid1);
            const valkyrie::NodalResults res2 = results_->nodalResults(nid2);

            // calculate strain
            std::shared_ptr<Property> prop = rod->get_property();
            std::shared_ptr<Material> matr = prop->get_material();

            // calculate displacements on local coordinate system
            double dx = n2->get_x() - n1->get_x();
            double dy = n2->get_y() - n1->get_y();
            double dz = n2->get_z() - n1->get_z();
            double eL = std::sqrt(dx*dx + dy*dy + dz*dz);
            double Cx = dx/eL;
            double Cy = dy/eL;
            double Cz = dz/eL;
            double A  = prop->get_A();
            double E  = matr->get_E();

            MatrixXd T(MAX_NODES_PER_ELEMENT, MAX_DOFS_PER_NODE * MAX_NODES_PER_ELEMENT);
            globalToLocal(Cx, Cy, Cz, T);

            VectorXd globalDisplacements(MAX_DOFS_PER_NODE * MAX_NODES_PER_ELEMENT);
            globalDisplacements(0) = res1.ux;
            globalDisplacements(1) = res1.uy;
            globalDisplacements(2) = res1.uz;
            globalDisplacements(3) = res2.ux;
            globalDisplacements(4) = res2.uy;
            globalDisplacements(5) = res2.uz;
            VectorXd localDisplacements = T * globalDisplacements;

            // strain
            double strain = (localDisplacements(1) - localDisplacements(0))/eL;
            double stress = strain * E;
            double force  = stress * A;
            results_->setElementalResult(rod_id, strain, stress, force);

        }

        StaticAnalysisResults *results_;
    };
}

StaticAnalysis::StaticAnalysis()
{
}

int StaticAnalysis::analyze(const Model& model, valkyrie::StaticAnalysisResults &results)
{
    size_t numberOfNodes = model.nodes_num();

    if (numberOfNodes > MAX_ALLOWABLE_NODES * MAX_DOFS_PER_NODE)
    {
        return kStaticAnalysisFailure; // empty results
    }

    int n = numberOfNodes;

    // node ids might not be continuous, so we
    // do a mapping from node-id to row_id
    std::map<int, int> nid2row; // node_id : row_id

    // stiffness matrix
    MatrixXd K = MatrixXd::Zero(n * MAX_DOFS_PER_NODE, n * MAX_DOFS_PER_NODE); // TODO: sparse matrix
    
    std::for_each(model.beginElems(), model.endElems(), updateStiffness(K, &nid2row));
    // force vector
    VectorXd F = VectorXd::Zero(n * MAX_DOFS_PER_NODE);
    std::for_each(model.beginForces(), model.endForces(), updateLoads(F, &nid2row));

    // copy global matrix (NOTE: we would never do this shit on a real FEM program)
    MatrixXd Kglobal(K);

#ifdef D_PRINT_FINAL_SYSTEM
    std::cout << "A = \n" << K << "\n";
    std::cout << "F = \n" << F << "\n";
#endif   
    
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

#ifdef D_PRINT_FINAL_SYSTEM
    std::cout << "A = \n" << K << "\n";
    std::cout << "F = \n" << F << "\n";
#endif   

    // solution phase
    Eigen::LLT<MatrixXd> llt;
    Eigen::ComputationInfo cinfo;
    llt.compute(K);
    cinfo = llt.info();

    if (cinfo == Eigen::Success)
    {
        VectorXd x = llt.solve(F);
        VectorXd r = Kglobal * x - F;
        for_each(model.beginNodes(), model.endNodes(), updateNodalResults(nid2row, x, r, &results));
        for_each(model.beginElems(), model.endElems(), updateElementalResults(&results));
    } else
    {
        return kStaticAnalysisFailure;
    }
    return kStaticAnalysisSuccess;
}

void valkyrie::StaticAnalysisResults::setNodalResult(int nid, double ux, double uy, double uz, double rx, double ry, double rz)
{
    valkyrie::NodalResults results;
    results.ux = ux;
    results.uy = uy;
    results.uz = uz;
    results.reactionX = rx;
    results.reactionY = ry;
    results.reactionZ = rz;
    nodalResults_[nid] = results;
}

void StaticAnalysisResults::setElementalResult(int eid, double strain, double stress, double force)
{
    valkyrie::ElementalResults results;
    results.strain = strain;
    results.stress = stress;
    results.force = force;
    elementalResults_[eid] = results;
}

#undef MAX_ALLOWABLE_NODES
#undef MAX_DOFS_PER_NODE
#undef MAX_NODES_PER_ELEMENT

