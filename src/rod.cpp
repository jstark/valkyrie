#include "rod.h"
#include "property.h"
#include "node.h"

using valkyrie::Rod;
using valkyrie::Node;
using valkyrie::Property;

Rod::Rod(int id, const std::string &name, std::shared_ptr<Property> p, std::shared_ptr<Node> n1, std::shared_ptr<Node> n2)
    : Entity(id, name), p_(p), n1_(n1), n2_(n2) {}

std::shared_ptr<Rod> valkyrie::try_create_rod(int eid, std::shared_ptr<Property> p, std::shared_ptr<Node> n1, std::shared_ptr<Node> n2, const std::string& name)
{
    Rod *r = 0;
    if (p && n1 && n2 && (n1 != n2))
    {
        r = new Rod(eid, name, p, n1, n2);
    }
    return make_shared(r);
}
