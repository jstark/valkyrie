#ifndef VALKYRIE_SPC_H_INCLUDED
#define VALKYRIE_SPC_H_INCLUDED

#include "entity.h"
#include <string>
#include <boost/shared_ptr.hpp>

using boost::shared_ptr;

namespace valkyrie
{

class Node;

#define kTranslateXDof  1 << 0
#define kTranslateYDof  2 << 0
#define kTranslateZDof  3 << 0

class Spc : private Entity
{
public:
    Spc(int id, const std::string& name, int dofs, shared_ptr<Node> n);

    IS_ENTITY

    shared_ptr<Node> node();
private:
    shared_ptr<Node> n_;
    int dofs_;
};//~ cl:Spc

}//~ ns:valkyrie

#endif // VALKYRIE_SPC_H_INCLUDED
