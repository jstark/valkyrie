#ifndef VALKYRIE_MATERIAL_H_INCLUDED
#define VALKYRIE_MATERIAL_H_INCLUDED

#include "entity.h"
#include <string>

namespace valkyrie
{

class Material : private Entity
{
public:
    Material(int id, const std::string& name, double E = 2.1e11, double rho = 7800.0);

    IS_ENTITY

    const double get_E() const { return E_; }
    const double get_rho() const { return rho_; }
private:
    double E_;
    double rho_;
};//~cl:Material

}//~ns:valkyrie

#endif // VALKYRIE_MATERIAL_H_INCLUDED
