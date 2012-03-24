#ifndef VALKYRIE_MODEL_H_INCLUDED
#define VALKYRIE_MODEL_H_INCLUDED

#include "valkyrie.h"
#include "entity.h"

#include <string>
#include <map>
#include <iostream>

#include <boost/shared_ptr.hpp>

namespace valkyrie
{

class Node;

class DLL_PUBLIC Model : private Entity
{
public:
    Model(int id, const std::string& name);

    bool addNode(boost::shared_ptr<Node> node);
private:
    std::map<int, boost::shared_ptr<Node> > nodes_;
};//~Model

}//~ns:valkyrie

#endif // VALKYRIE_MODEL_H_INCLUDED
