#include "rod.h"
#include "property.h"
#include "node.h"

using valkyrie::Rod;
using valkyrie::Node;
using valkyrie::Property;

Rod::Rod(int id, const std::string &name, shared_ptr<Property> p, shared_ptr<Node> n1, shared_ptr<Node> n2)
    : Entity(id, name), p_(p), n1_(n1), n2_(n2) {}

shared_ptr<Property> Rod::property()
{
    return p_;
}

shared_ptr<Node> Rod::node_1()
{
    return n1_;
}

shared_ptr<Node> Rod::node_2()
{
    return n2_;
}
