#include "property.h"
#include "material.h"

using valkyrie::Property;
using valkyrie::Material;

Property::Property(int pid, const std::string &name, shared_ptr<Material> m, double A)
    : Entity(pid, name), m_(m), A_(A) {}

shared_ptr<Property> valkyrie::try_create_property(int pid, shared_ptr<Material> m, double A, const std::string& name)
{
    Property *p = 0;
    if (A > 0 && m)
    {
        LOG("[ctor][property]{pid = %d, name = %s, mid = %d, A = %le}\n", pid, name.c_str(), m->get_id(), A)
        p = new Property(pid, name, m, A);
    }
    return make_shared(p);
}
