#ifndef VALKYRIE_ROD_H_INCLUDED
#define VALKYRIE_ROD_H_INCLUDED

#include "valkyrie.h"
#include "entity.h"
#include <string>
#include <memory>

namespace valkyrie
{

class Property;
class Node;

class DLL_HIDDEN Rod : private Entity
{
public:
    Rod(int id, const std::string& name, std::shared_ptr<Property> p, std::shared_ptr<Node> n1, std::shared_ptr<Node> n2);

    IS_ENTITY

    std::shared_ptr<Property> get_property() { return p_; }
    std::shared_ptr<Node> get_node1() { return n1_; }
    std::shared_ptr<Node> get_node2() { return n2_; }
private:
    std::shared_ptr<Property> p_;
    std::shared_ptr<Node> n1_;
    std::shared_ptr<Node> n2_;
};//~ cl:Rod

std::shared_ptr<Rod> DLL_HIDDEN try_create_rod(int eid, std::shared_ptr<Property> p, std::shared_ptr<Node> n1, std::shared_ptr<Node> n2, const std::string& name);

}//~ns:valkyrie

#endif // VALKYRIE_ROD_H_INCLUDED
