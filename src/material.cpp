#include "material.h"

using valkyrie::Material;

Material::Material(int id, const std::string &name, double E, double rho)
    : Entity(id, name), E_(E), rho_(rho) {}

std::shared_ptr<Material> valkyrie::try_create_material(int mid, double E, double rho, const std::string& name)
{
    std::shared_ptr<Material> m;
    if (E > 0. && rho > 0.)
    {
        LOG("[ctor][material]{mid = %d, name = %s, E = %le, rho = %le}\n", mid, name.c_str(), E, rho)
        m = std::make_shared<Material>(mid, name, E, rho);
    }
    return m;
}
