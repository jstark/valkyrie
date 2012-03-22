#ifndef VALKYRIE_NODE_H_INCLUDED
#define VALKYRIE_NODE_H_INCLUDED

namespace valkyrie
{

class Node
{
public:
    Node(int id, double x, double y, double z = 0.0);

    int get_id() const;
    double get_x() const;
    double get_y() const;
    double get_z() const;

private:
    int id_;
    double x_;
    double y_;
    double z_;
};//~cl:Node

}//~ns:valkyrie

#endif // VALKYRIE_NODE_H_INCLUDED
