#include "valkyrie.h"
#include "entity.h"
#include "model.h"
#include <string>
#include <map>
#include <boost/shared_ptr.hpp>

using valkyrie::EntityDb;
using valkyrie::Model;
using std::map;
using boost::shared_ptr;

namespace
{
    EntityDb<Model> models;
}

#define TRY_CREATE(what, mid, ...) \
    shared_ptr<Model> realModel = models.find(mid); \
    if (realModel) { \
        return realModel->create##what(__VA_ARGS__);\
    }\
    return kActionFailed | kActionErrorIdAlreadyExists;

extern "C" int VKModelCreate(int mid, const char *name)
{
    if (models.find(mid))
    {
        return kActionFailed | kActionErrorIdAlreadyExists;
    }
    models.add(shared_ptr<Model>(new Model(mid, std::string(name ? name : ""))));
    return kActionOK;
}

extern "C" int VKModelCreateNode(int mid, int nid, double x, double y, double z)
{
    TRY_CREATE(Node, mid, nid, x, y, z)
}

extern "C" int VKModelCreateMaterial(int modelid, int matid, double E, double rho, const char *name)
{
    TRY_CREATE(Material, modelid, matid, E, rho, name);
}

extern "C" int VKModelCreateProperty(int mid, int pid, int matid, double A, const char *name)
{
    TRY_CREATE(Property, mid, pid, matid, A, name);
}

extern "C" int VKModelCreateRod(int mid, int rid, int pid, int n1, int n2)
{
    TRY_CREATE(Rod, mid, rid, pid, n1, n2);
}

extern "C" int VKModelCreateSpc(int mid, int sid, int dofs, int nid)
{
    TRY_CREATE(Spc, mid, sid, dofs, nid);
}

extern "C" int VKModelCreateForce(int mid, int fid, int nid, double magn, double nx, double ny, double nz)
{
    TRY_CREATE(Force, mid, fid, nid, magn, nx, ny, nz);
}
