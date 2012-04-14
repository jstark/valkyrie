#ifndef VALKYRIE_NODE_H_INCLUDED
#define VALKYRIE_NODE_H_INCLUDED

#include "valkyrie.h"
#include "entity.h"

namespace valkyrie
{

class DLL_HIDDEN Node : private Entity
{
public:
    Node(int id, double x, double y, double z = 0.0);
    ~Node();

    IS_ENTITY

    const double get_x() const { return x_; }
    const double get_y() const { return y_; }
    const double get_z() const { return z_; }

private:
    double x_;
    double y_;
    double z_;
};//~cl:Node

}//~ns:valkyrie

#endif // VALKYRIE_NODE_H_INCLUDED
