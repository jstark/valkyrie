#include "property.h"

using valkyrie::Property;

Property::Property(int id, const std::string &name, double A)
    : Entity(id, name), A_(A) {}

const double Property::get_A() const
{
    return A_;
}


