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
    int createRod(int eid, int pid, int nid_i, int nid_j);
    int createSpc(int sid, int dofs, int nid);
    int createForce(int fid, int nid, double magn, double nx, double ny, double nz);
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
