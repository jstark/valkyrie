#ifndef VALKYRIE_PROPERTY_H_INCLUDED
#define VALKYRIE_PROPERTY_H_INCLUDED

#include "entity.h"
#include <string>

namespace valkyrie
{

class Property : private Entity
{
public:
    Property(int id, const std::string &name, double A);

    IS_ENTITY

    const double get_A() const;
private:
    double A_;
};//~cl:Property

}//~ns:valkyrie

#endif // VALKYRIE_PROPERTY_H_INCLUDED
