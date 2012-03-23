#ifndef VALKYRIE_NODE_H_INCLUDED
#define VALKYRIE_NODE_H_INCLUDED

namespace valkyrie
{

class Node
{
public:
    Node(int id, double x, double y, double z = 0.0);

    const int get_id() const;
    const double get_x() const;
    const double get_y() const;
    const double get_z() const;

private:
    int id_;
    double x_;
    double y_;
    double z_;
};//~cl:Node

}//~ns:valkyrie

#endif // VALKYRIE_NODE_H_INCLUDED
