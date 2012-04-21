#include "node.h"
#include <iostream>

using valkyrie::Entity;
using valkyrie::Node;

Node::Node(int id, double x, double y, double z)
    : Entity(id), x_(x), y_(y), z_(z) {}

Node::~Node()
{
}
