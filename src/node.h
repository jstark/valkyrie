#ifndef VALKYRIE_NODE_H_INCLUDED
#define VALKYRIE_NODE_H_INCLUDED

#include "entity.h"

namespace valkyrie
{

class Node : private Entity
{
public:
    Node(int id, double x, double y, double z = 0.0);

    IS_ENTITY

    const double get_x() const;
    const double get_y() const;
    const double get_z() const;

private:
    double x_;
    double y_;
    double z_;
};//~cl:Node

}//~ns:valkyrie

#endif // VALKYRIE_NODE_H_INCLUDED
