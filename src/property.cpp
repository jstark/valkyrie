#include "property.h"

using valkyrie::Property;

Property::Property(int pid, const std::string &name, shared_ptr<Material> m, double A)
    : Entity(pid, name), m_(m), A_(A) {}


