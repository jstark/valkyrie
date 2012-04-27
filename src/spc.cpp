#include "spc.h"

using valkyrie::Spc;

Spc::Spc(int id, const std::string &name, int dofs, shared_ptr<Node> n)
    : Entity(id, name), n_(n), dofs_(dofs)
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
