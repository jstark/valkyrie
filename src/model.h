#ifndef VALKYRIE_MODEL_H_INCLUDED
#define VALKYRIE_MODEL_H_INCLUDED

#include "valkyrie.h"
#include "entity.h"

#include <string>

namespace valkyrie
{

class Node;
class Material;
class Property;
class Rod;
class Spc;
class Force;

class DLL_HIDDEN Model : private Entity
{
public:
    Model(int id, const std::string& name);
    ~Model();

    IS_ENTITY

    int createNode(int nid, double x, double y, double z = 0.0);
    int createMaterial(int mid, double E = 2.1e11, double rho = 7800.0, const std::string& name = "");
    int createProperty(int pid, int mid, double A, const std::string& name = "");

    typedef EntityDb<Rod>::const_iterator const_elem_iterator;
    const_elem_iterator beginElems() const { return elements_.begin(); }
    const_elem_iterator endElems() const { return elements_.end(); }
    int createRod(int eid, int pid, int nid_i, int nid_j);

    typedef EntityDb<Spc>::const_iterator const_spc_iterator;
    const_spc_iterator beginSpcs() const { return constraints_.begin(); }
    const_spc_iterator endSpcs() const { return constraints_.end(); }
    int createSpc(int sid, int dofs, int nid);

    typedef EntityDb<Force>::const_iterator const_force_iterator;
    int createForce(int fid, int nid, double magn, double nx, double ny, double nz);
    const_force_iterator beginForces() const { return loads_.begin(); }
    const_force_iterator endForces() const { return loads_.end(); }

    size_t nodes_num() const { return nodes_.size(); }
private:
    EntityDb<Node> nodes_;
    EntityDb<Material> materials_;
    EntityDb<Property> properties_;
    EntityDb<Rod> elements_;
    EntityDb<Spc> constraints_;
    EntityDb<Force> loads_;
};//~Model

}//~ns:valkyrie

#endif // VALKYRIE_MODEL_H_INCLUDED
