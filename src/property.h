#ifndef VALKYRIE_PROPERTY_H_INCLUDED
#define VALKYRIE_PROPERTY_H_INCLUDED

#include "entity.h"
#include <string>
#include <boost/shared_ptr.hpp>

namespace valkyrie
{

using boost::shared_ptr;

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

}//~ns:valkyrie

#endif // VALKYRIE_PROPERTY_H_INCLUDED
