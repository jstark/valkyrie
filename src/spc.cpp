#include "spc.h"

using valkyrie::Spc;

Spc::Spc(int id, const std::string &name, int dofs, shared_ptr<Node> n)
    : Entity(id, name), dofs_(dofs), n_(n)
{
}
