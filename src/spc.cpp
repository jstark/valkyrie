#include "spc.h"
#include "node.h"

using valkyrie::Spc;
using valkyrie::Node;

Spc::Spc(int id, const std::string &name, int dofs, shared_ptr<Node> n)
    : Entity(id, name), dofs_(dofs), n_(n)
{
}

shared_ptr<Spc> valkyrie::try_create_spc(int sid, int dofs, shared_ptr<Node> n)
{
    Spc *s = 0;
    if (n)
    {
        s = new Spc(sid, "", dofs, n);
    }
    return make_shared(s);
}
