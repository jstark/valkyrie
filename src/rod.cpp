#include "rod.h"

using valkyrie::Rod;

Rod::Rod(int id, const std::string &name, shared_ptr<Property> p, shared_ptr<Node> n1, shared_ptr<Node> n2)
    : Entity(id, name), p_(p), n1_(n1), n2_(n2) {}
