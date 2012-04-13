#include "model.h"
#include "node.h"
#include "material.h"
#include "property.h"
#include "rod.h"
#include "spc.h"
#include "force.h"

#include <iostream>
#include <cmath>
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

namespace
{

template<typename T> shared_ptr<T> make_shared(T* instance)
{
    return shared_ptr<T>(instance);
}

}

Model::Model(int id, const std::string& name)
    : Entity(id, name) {}

Model::~Model()
{
#ifdef LOG_DESTRUCTORS
    std::cout << "[Log]>Model::~Model <" << this << ">" << std::endl;
#endif
}

int Model::createNode(int id, double x, double y, double z)
{
    return nodes_.add(make_shared(new Node(id, x, y, z)));
}

namespace
{

shared_ptr<Material> try_create_material(int mid, double E, double rho, const std::string& name)
{
    Material *m = 0;
    if (E > 0. && rho > 0.)
    {
        m = new Material(mid, name, E, rho);
    }
    return make_shared(m);
}

shared_ptr<Property> try_create_property(int pid, shared_ptr<Material> m, double A, const std::string& name)
{
    Property *p = 0;
    if (A > 0 && m)
    {
        p = new Property(pid, name, m, A);
    }
    return make_shared(p);
}

shared_ptr<Rod> try_create_rod(int eid, shared_ptr<Property> p, shared_ptr<Node> n1, shared_ptr<Node> n2, const std::string& name)
{
    Rod *r = 0;
    if (p && n1 && n2 && (n1 != n2))
    {
        r = new Rod(eid, name, p, n1, n2);
    }
    return make_shared(r);
}

shared_ptr<Spc> try_create_spc(int sid, int dofs, shared_ptr<Node> n)
{
    Spc *s = 0;
    if (n)
    {
        s = new Spc(sid, "", dofs, n);
    }
    return make_shared(s);
}

int unit_vector(double x, double y, double z, double *nx, double *ny, double *nz)
{
    int ret = 0;

    double len = std::sqrt(x*x + y*y + z*z);

    if (len < 1.0e-6)
    {
        return 1; // error
    }

    *nx = x/len;
    *ny = y/len;
    *nz = z/len;

    return ret;
}

shared_ptr<Force> try_create_force(int fid, shared_ptr<Node> n, double magn, double nx, double ny, double nz)
{
    Force *f = 0;
    if (n && !unit_vector(nx, ny, nz, &nx, &ny, &nz))
    {
        f = new Force(fid, "", n, magn, nx, ny, nz);
    }
    return make_shared(f);
}

}//~ns:

int Model::createMaterial(int mid, double E, double rho, const std::string &name)
{
    shared_ptr<Material> m = try_create_material(mid, E, rho, name);
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
