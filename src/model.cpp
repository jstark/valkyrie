#include "model.h"

using valkyrie::Model;

Model::Model(const std::string& modelName)
    : name_(modelName)
{
}

const std::string Model::get_name() const
{
    return name_;
}
