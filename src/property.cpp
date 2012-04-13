#include "property.h"

using valkyrie::Property;

Property::Property(int pid, const std::string &name, shared_ptr<Material> m, double A)
    : Entity(pid, name), m_(m), A_(A) {}

shared_ptr<Property> valkyrie::try_create_property(int pid, shared_ptr<Material> m, double A, const std::string& name)
{
    Property *p = 0;
    if (A > 0 && m)
    {
        p = new Property(pid, name, m, A);
    }
    return make_shared(p);
}
