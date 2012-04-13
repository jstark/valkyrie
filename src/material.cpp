#include "material.h"

using valkyrie::Material;

Material::Material(int id, const std::string &name, double E, double rho)
    : Entity(id, name), E_(E), rho_(rho) {}
