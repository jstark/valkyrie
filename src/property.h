#ifndef VALKYRIE_PROPERTY_H_INCLUDED
#define VALKYRIE_PROPERTY_H_INCLUDED

#include "entity.h"
#include <string>
#include <boost/shared_ptr.hpp>

using boost::shared_ptr;

namespace valkyrie
{

class Material;

class Property : private Entity
{
public:
    Property(int pid, const std::string &name, shared_ptr<Material> m, double A);

    IS_ENTITY

    const double get_A() const { return A_; }
private:
    shared_ptr<Material> m_;
    double A_;

};//~cl:Property

shared_ptr<Property> try_create_property(int pid, shared_ptr<Material> m, double A, const std::string& name);

}//~ns:valkyrie

#endif // VALKYRIE_PROPERTY_H_INCLUDED
