#ifndef VALKYRIE_SPC_H_INCLUDED
#define VALKYRIE_SPC_H_INCLUDED

#include "valkyrie.h"
#include "entity.h"
#include <string>
#include <boost/shared_ptr.hpp>

using boost::shared_ptr;

namespace valkyrie
{

class Node;

#define kTranslateXDof  1
#define kTranslateYDof  2
#define kTranslateZDof  4

class DLL_HIDDEN Spc : private Entity
{
public:
    Spc(int id, const std::string& name, int dofs, shared_ptr<Node> n);

    IS_ENTITY

    shared_ptr<Node> get_node() { return n_; }
    bool is_constrained_at(int dof) { return dofs_ & dof; }
private:
    shared_ptr<Node> n_;
    int dofs_;
};//~ cl:Spc

shared_ptr<Spc> DLL_HIDDEN try_create_spc(int sid, int dofs, shared_ptr<Node> n);

}//~ ns:valkyrie

#endif // VALKYRIE_SPC_H_INCLUDED
