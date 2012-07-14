#ifndef VALKYRIE_SPC_H_INCLUDED
#define VALKYRIE_SPC_H_INCLUDED

#include "valkyrie.h"
#include "entity.h"
#include <string>
#include <memory>


namespace valkyrie
{

class Node;

class DLL_HIDDEN Spc : private Entity
{
public:
    Spc(int id, const std::string& name, int dofs, std::shared_ptr<Node> n);

    IS_ENTITY

    std::shared_ptr<Node> get_node() { return n_; }
    const bool is_constrained_at(int dof) { return (dofs_ & dof) ? true : false; }
private:
    std::shared_ptr<Node> n_;
    int dofs_;
};//~ cl:Spc

std::shared_ptr<Spc> DLL_HIDDEN try_create_spc(int sid, int dofs, std::shared_ptr<Node> n);

}//~ ns:valkyrie

#endif // VALKYRIE_SPC_H_INCLUDED
