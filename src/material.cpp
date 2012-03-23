#include "material.h"

using valkyrie::Material;

Material::Material(int id, const std::string &name, double E, double rho)
    : id_(id), name_(name), E_(E), rho_(rho)
{
}

const int Material::get_id() const
{
    return id_;
}

const std::string Material::get_name() const
{
    return name_;
}

const double Material::get_E() const
{
    return E_;
}

const double Material::get_rho() const
{
    return rho_;
}
