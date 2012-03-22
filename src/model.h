#ifndef VALKYRIE_MODEL_H_INCLUDED
#define VALKYRIE_MODEL_H_INCLUDED

#include <string>

namespace valkyrie
{

class Model
{
public:
    explicit Model(const std::string& name);

    /* properties */
    const std::string get_name() const;
private:
    const std::string name_;
};//~Model

}//~ns:valkyrie

#endif // VALKYRIE_MODEL_H_INCLUDED
