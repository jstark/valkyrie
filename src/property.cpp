#include "property.h"
#include "material.h"

using valkyrie::Property;
using valkyrie::Material;

Property::Property(int pid, const std::string &name, std::shared_ptr<Material> m, double A)
    : Entity(pid, name), m_(m), A_(A) {}

std::shared_ptr<Property> valkyrie::try_create_property(int pid, std::shared_ptr<Material> m, double A, const std::string& name)
{
    Property *p = 0;
    if (A > 0 && m)
    {
        LOG("[ctor][property]{pid = %d, name = %s, mid = %d, A = %le}\n", pid, name.c_str(), m->get_id(), A)
        p = new Property(pid, name, m, A);
    }
    return make_shared(p);
}
