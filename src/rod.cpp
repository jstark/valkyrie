#include "rod.h"

using valkyrie::Rod;

Rod::Rod(int id, const std::string &name, shared_ptr<Property> p, shared_ptr<Node> n1, shared_ptr<Node> n2)
    : Entity(id, name), p_(p), n1_(n1), n2_(n2) {}

shared_ptr<Rod> valkyrie::try_create_rod(int eid, shared_ptr<Property> p, shared_ptr<Node> n1, shared_ptr<Node> n2, const std::string& name)
{
    Rod *r = 0;
    if (p && n1 && n2 && (n1 != n2))
    {
        r = new Rod(eid, name, p, n1, n2);
    }
    return make_shared(r);
}
