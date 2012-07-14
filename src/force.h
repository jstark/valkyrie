#ifndef VALKYRIE_FORCE_H_INCLUDED
#define VALKYRIE_FORCE_H_INCLUDED

#include <memory>
#include "valkyrie.h"
#include "entity.h"
#include <string>

namespace valkyrie
{

class Node;

class DLL_HIDDEN Force : private Entity
{
public:
    Force(int id, const std::string& name, std::shared_ptr<Node> n, double magn, double nx, double ny, double nz);

    IS_ENTITY

    std::shared_ptr<Node> get_node() { return n_; }
    const double magnitude() const { return magnitude_; }
    const double nx() const { return nx_; }
    const double ny() const { return ny_; }
    const double nz() const { return nz_; }
private:
    std::shared_ptr<Node> n_;
    double magnitude_;
    double nx_, ny_, nz_;
};

std::shared_ptr<Force> DLL_HIDDEN try_create_force(int fid, std::shared_ptr<Node> n, double magn, double nx, double ny, double nz);

}//~ns:valkyrie

#endif // VALKYRIE_FORCE_H_INCLUDED
