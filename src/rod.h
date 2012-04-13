#ifndef VALKYRIE_ROD_H_INCLUDED
#define VALKYRIE_ROD_H_INCLUDED

#include "entity.h"
#include <string>
#include <boost/shared_ptr.hpp>

using boost::shared_ptr;

namespace valkyrie
{

class Property;
class Node;

class Rod : private Entity
{
public:
    Rod(int id, const std::string& name, shared_ptr<Property> p, shared_ptr<Node> n1, shared_ptr<Node> n2);

    IS_ENTITY

    shared_ptr<Property> property() { return p_; }
    shared_ptr<Node> node_1() { return n1_; }
    shared_ptr<Node> node_2() { return n2_; }
private:
    shared_ptr<Property> p_;
    shared_ptr<Node> n1_;
    shared_ptr<Node> n2_;
};//~ cl:Rod

shared_ptr<Rod> try_create_rod(int eid, shared_ptr<Property> p, shared_ptr<Node> n1, shared_ptr<Node> n2, const std::string& name);

}//~ns:valkyrie

#endif // VALKYRIE_ROD_H_INCLUDED
