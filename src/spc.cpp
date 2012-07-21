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
    std::shared_ptr<Spc> s;
    if (n)
    {
        LOG("[ctor][spc]{sid = %d, dofs = %d, node = %d}\n", sid, dofs, n->get_id());
        s = std::make_shared<Spc>(sid, "", dofs, n);
    }
    return s;
}
