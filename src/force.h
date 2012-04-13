#ifndef VALKYRIE_FORCE_H_INCLUDED
#define VALKYRIE_FORCE_H_INCLUDED

#include "entity.h"
#include <string>
#include <boost/shared_ptr.hpp>

namespace valkyrie
{

using boost::shared_ptr;

class Node;

class Force : private Entity
{
public:
    Force(int id, const std::string& name, shared_ptr<Node> n, double magn, double nx, double ny, double nz);

    IS_ENTITY
private:
    shared_ptr<Node> n_;
    double magnitude_;
    double nx_, ny_, nz_;
};

}//~ns:valkyrie

#endif // VALKYRIE_FORCE_H_INCLUDED
