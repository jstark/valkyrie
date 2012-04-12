#ifndef VALKYRIE_ROD_H_INCLUDED
#define VALKYRIE_ROD_H_INCLUDED

#include "entity.h"
#include <string>
#include <boost/shared_ptr.hpp>

namespace valkyrie
{

using boost::shared_ptr;

class Property;
class Node;

class Rod : private Entity
{
public:
    Rod(int id, const std::string& name, shared_ptr<Property> p, shared_ptr<Node> n1, shared_ptr<Node> n2);

    IS_ENTITY

private:
    shared_ptr<Property> p_;
    shared_ptr<Node> n1_;
    shared_ptr<Node> n2_;
};//~ cl:Rod

}//~ns:valkyrie

#endif // VALKYRIE_ROD_H_INCLUDED
