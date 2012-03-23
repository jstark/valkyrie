#include "model.h"
#include "node.h"

using valkyrie::Model;
using valkyrie::Node;

Model::Model(const std::string& modelName)
    : name_(modelName)
{
}

bool Model::addNode(boost::shared_ptr<Node> node)
{
    return nodes_.insert(std::make_pair(node->get_id(), node)).second;
}

const std::string Model::get_name() const
{
    return name_;
}
