#ifndef VALKYRIE_PROPERTY_H_INCLUDED
#define VALKYRIE_PROPERTY_H_INCLUDED

#include <string>

namespace valkyrie
{

class Property
{
public:
    Property(int id, const std::string &name, double A);

    const int get_id() const;
    const std::string get_name() const;
    const double get_A() const;
private:
    int id_;
    const std::string name_;
    double A_;
};//~cl:Property

}//~ns:valkyrie

#endif // VALKYRIE_PROPERTY_H_INCLUDED
