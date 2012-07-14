#include "spc.h"
#include "node.h"

using valkyrie::Spc;
using valkyrie::Node;

Spc::Spc(int id, const std::string &name, int dofs, std::shared_ptr<Node> n)
    : Entity(id, name), n_(n), dofs_(dofs)
{
}

std::shared_ptr<Spc> valkyrie::try_create_spc(int sid, int dofs, std::shared_ptr<Node> n)
{
    Spc *s = 0;
    if (n)
    {
        LOG("[ctor][spc]{sid = %d, dofs = %d, node = %d}\n", sid, dofs, n->get_id());
        s = new Spc(sid, "", dofs, n);
    }
    return make_shared(s);
}
