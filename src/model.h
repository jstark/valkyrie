#ifndef VALKYRIE_MODEL_H_INCLUDED
#define VALKYRIE_MODEL_H_INCLUDED

#include "valkyrie.h"
#include "entity.h"

#include <string>

namespace valkyrie
{

class Node;

class DLL_PUBLIC Model : private Entity
{
public:
    Model(int id, const std::string& name);
    ~Model();

    IS_ENTITY

    int createNode(int id, double x, double y, double z = 0.0);
private:
    EntityDb<Node> nodes_;
};//~Model

}//~ns:valkyrie

#endif // VALKYRIE_MODEL_H_INCLUDED
