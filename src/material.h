#ifndef VALKYRIE_MATERIAL_H_INCLUDED
#define VALKYRIE_MATERIAL_H_INCLUDED

#include <string>

namespace valkyrie
{

class Material
{
public:
    Material(int id, const std::string& name, double E = 2.1e11, double rho = 7800.0);

    const int get_id() const;
    const std::string get_name() const;
    const double get_E() const;
    const double get_rho() const;
private:
    int id_;
    double E_;
    double rho_;
    std::string name_;
};//~cl:Material

}//~ns:valkyrie

#endif // VALKYRIE_MATERIAL_H_INCLUDED
