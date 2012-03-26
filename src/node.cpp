#include "node.h"
#include <iostream>

using valkyrie::Entity;
using valkyrie::Node;

Node::Node(int id, double x, double y, double z)
    : Entity(id), x_(x), y_(y), z_(z) {}

Node::~Node()
{
#ifdef LOG_DESTRUCTORS
    std::cout << "[Log]>Node::~Node <" << this << ">" << std::endl;
#endif
}

const double Node::get_x() const
{
    return x_;
}

const double Node::get_y() const
{
    return y_;
}

const double Node::get_z() const
{
    return z_;
}
