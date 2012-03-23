#include "property.h"

using valkyrie::Property;

Property::Property(int id, const std::string &name, double A)
    : id_(id), name_(name), A_(A)
{
}

const int Property::get_id() const
{
    return id_;
}

const std::string Property::get_name() const
{
    return name_;
}

const double Property::get_A() const
{
    return A_;
}


