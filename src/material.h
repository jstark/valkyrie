#ifndef VALKYRIE_MATERIAL_H_INCLUDED
#define VALKYRIE_MATERIAL_H_INCLUDED

#include "entity.h"
#include <string>
#include <boost/shared_ptr.hpp>

using boost::shared_ptr;

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

shared_ptr<Material> try_create_material(int mid, double E, double rho, const std::string& name);

}//~ns:valkyrie

#endif // VALKYRIE_MATERIAL_H_INCLUDED
