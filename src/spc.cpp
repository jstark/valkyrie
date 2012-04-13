#include "spc.h"
#include "node.h"

using valkyrie::Spc;
using valkyrie::Node;

Spc::Spc(int id, const std::string &name, int dofs, shared_ptr<Node> n)
    : Entity(id, name), dofs_(dofs), n_(n)
{
}

shared_ptr<Node> Spc::node()
{
    return n_;
}
