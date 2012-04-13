#include "material.h"

using valkyrie::Material;

Material::Material(int id, const std::string &name, double E, double rho)
    : Entity(id, name), E_(E), rho_(rho) {}

shared_ptr<Material> valkyrie::try_create_material(int mid, double E, double rho, const std::string& name)
{
    Material *m = 0;
    if (E > 0. && rho > 0.)
    {
        m = new Material(mid, name, E, rho);
    }
    return make_shared(m);
}
