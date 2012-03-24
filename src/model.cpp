#include "model.h"
#include "node.h"

using valkyrie::Model;
using valkyrie::Node;

Model::Model(int id, const std::string& name)
    : Entity(id, name) {}

bool Model::addNode(boost::shared_ptr<Node> node)
{
    return nodes_.insert(std::make_pair(node->get_id(), node)).second;
}
