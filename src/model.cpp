#include "model.h"
#include "node.h"
#include "material.h"
#include "property.h"
#include "rod.h"
#include "spc.h"
#include "force.h"

#include <iostream>
#include <boost/shared_ptr.hpp>

using valkyrie::Entity;
using valkyrie::Model;
using valkyrie::Node;
using valkyrie::Material;
using valkyrie::Property;
using valkyrie::Rod;
using valkyrie::Spc;
using valkyrie::Force;

using boost::shared_ptr;

Model::Model(int id, const std::string& name)
    : Entity(id, name) {}

Model::~Model()
{
}

int Model::createNode(int id, double x, double y, double z)
{
    return nodes_.add(make_shared(new Node(id, x, y, z)));
}

int Model::createMaterial(int mid, double E, double rho, const std::string &name)
{
    shared_ptr<Material> m = valkyrie::try_create_material(mid, E, rho, name);
    if (m)
    {
        return materials_.add(m);
    }
    return kActionFailed | kActionErrorInvalidArgs;
}

int Model::createProperty(int pid, int mid, double A, const std::string &name)
{
    shared_ptr<Material> m = materials_.find(mid);
    shared_ptr<Property> p = try_create_property(pid, m, A, name);
    if (p)
    {
        return properties_.add(p);
    }
    return kActionFailed | kActionErrorInvalidArgs;
}

int Model::createRod(int eid, int pid, int nid_i, int nid_j)
{
    shared_ptr<Property> p = properties_.find(pid);
    shared_ptr<Node> n1 = nodes_.find(nid_i);
    shared_ptr<Node> n2 = nodes_.find(nid_j);
    shared_ptr<Rod> rod = try_create_rod(eid, p, n1, n2, "");
    if (rod)
    {
        return elements_.add(rod);
    }
    return kActionFailed | kActionErrorInvalidArgs;
}

int Model::createSpc(int sid, int dof, int nid)
{
    shared_ptr<Node> n = nodes_.find(nid);
    shared_ptr<Spc > s = try_create_spc(sid, dof, n);
    if (s)
    {
        return constraints_.add(s);
    }
    return kActionFailed | kActionErrorInvalidArgs;
}

int Model::createForce(int fid, int nid, double magn, double nx, double ny, double nz)
{
    shared_ptr<Node> n = nodes_.find(nid);
    shared_ptr<Force> f= try_create_force(fid, n, magn, nx, ny, nz);
    if (f)
    {
        return loads_.add(f);
    }
    return kActionFailed | kActionErrorInvalidArgs;
}
