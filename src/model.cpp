#include "model.h"
#include "node.h"

#include <boost/shared_ptr.hpp>

using valkyrie::Entity;
using valkyrie::Model;
using valkyrie::Node;

using boost::shared_ptr;

namespace
{

template<typename T> shared_ptr<T> make_shared(T* instance)
{
    return shared_ptr<T>(instance);
}

}

Model::Model(int id, const std::string& name)
    : Entity(id, name) {}

int Model::createNode(int id, double x, double y, double z)
{
    return nodes_.add(make_shared(new Node(id, x, y, z)));
}
