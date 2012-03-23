#include "node.h"

using valkyrie::Node;

Node::Node(int id, double x, double y, double z)
    : id_(id), x_(x), y_(y), z_(z)
{
}

const int valkyrie::Node::get_id() const
{
    return id_;
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
